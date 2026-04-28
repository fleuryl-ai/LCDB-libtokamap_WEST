#!/usr/bin/env python3
import argparse
import importlib.util
import json
import os
import re
import sys
from collections import defaultdict


class Node:
    """A node in the hierarchical representation of the IDS structure."""
    def __init__(self, name):
        self.name = name
        self.children = {}
        self.mapping_info = None
        self.ids_path = None


def load_structures(ids_name, structures_file):
    """Loads the structures module dynamically from a .py file."""
    if os.path.isdir(structures_file):
        structures_file = os.path.join(structures_file, f"{ids_name}_structures.py")
    
    spec = importlib.util.spec_from_file_location(ids_name, structures_file)
    if spec is None:
        print(f"Error: Could not load structures from {structures_file}", file=sys.stderr)
        sys.exit(1)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return {s.name: s for s in module.structures}


def get_field_info(ids_path, root_struct_name, structures_map):
    """Resolves the type and rank of a field given its IDS path."""
    clean_path = re.sub(r'\[.*?\]', '', ids_path)
    tokens = clean_path.split('/')
    
    current_struct_name = root_struct_name
    if current_struct_name not in structures_map and f"{current_struct_name}_struct" in structures_map:
        current_struct_name = f"{current_struct_name}_struct"

    for i, token in enumerate(tokens):
        if current_struct_name not in structures_map: return "unknown", 0
        struct = structures_map[current_struct_name]
        field = next((f for f in struct.fields if f.name == token or f.name == f"{token}_vect"), None)
        if field is None: return "unknown", 0
        if i == len(tokens) - 1: return field.type_name, field.rank
        
        if field.is_vector or field.is_struct:
            type_name = field.type_name
            if "std::vector" in type_name:
                match = re.search(r'<(\w+)>', type_name)
                current_struct_name = match.group(1) if match else "unknown"
            else:
                current_struct_name = type_name.replace('*', '')
        else:
            return "unknown", 0
    return "unknown", 0


def python_type_to_cpp_type(py_type, rank):
    """Converts a Python/IMAS type string to a C++ type string, handling NDData for rank > 1."""
    base_type = py_type.replace("*", "")

    # This handles std::vector<some_struct> which has rank 0 in our definition
    if "std::vector" in base_type:
        return base_type

    if rank == 0:
        return base_type
    if rank == 1:
        return f"std::vector<{base_type}>"
    
    # For rank > 1, use NDData
    return f"NDData<{base_type}>"


def get_default_cpp_value(cpp_type):
    """Returns a default value string for a given C++ type."""
    if "string" in cpp_type: return '""'
    if cpp_type.startswith("NDData"): return '{}'
    if "vector" in cpp_type: return '{}'
    if "double" in cpp_type or "float" in cpp_type: return '0.0'
    if "int" in cpp_type: return '0'
    return '""'


def map_path_to_cpp_parts(path):
    """Creates a C++ function name and argument definition from an IDS path."""
    clean_path = path.replace('[#]', '').replace('/', '_')
    func_name = f"get_{clean_path}"
    num_indices = path.count('[#]')
    args_def = [f"size_t idx_{i}" for i in range(num_indices)]
    return func_name, f"({', '.join(args_def)})"


def build_tree(mappings):
    """Builds a hierarchical tree from the flat mapping paths."""
    root = Node("root")
    for path, info in sorted(mappings.items()):
        if path.startswith('_') or path == 'version': continue
        
        current_node = root
        # Use a sentinel to represent array elements in the path
        parts = path.replace('[#]', '/_array_element_').split('/')
        
        for part in parts:
            if not part: continue
            if part not in current_node.children:
                current_node.children[part] = Node(part)
            current_node = current_node.children[part]
            
        current_node.mapping_info = info
        current_node.ids_path = path
    return root


def generate_protected_methods(mappings, ids_name, structures_map):
    """Generates the C++ code for the protected virtual methods."""
    methods = []
    for path, info in sorted(mappings.items()):
        # Ensure that the mapping info is a dictionary before processing.
        if not isinstance(info, dict):
            continue

        map_type = info.get("map_type", info.get("MAP_TYPE"))
        if map_type not in ["DATA_SOURCE", "DIMENSION"] or path.startswith('_'):
            continue

        func_name, args_def = map_path_to_cpp_parts(path)
        
        if map_type == "DIMENSION":
            return_type = "size_t"
            default_value = "2"
        else: # DATA_SOURCE
            py_type, rank = get_field_info(path, ids_name, structures_map)
            return_type = python_type_to_cpp_type(py_type, rank)
            default_value = get_default_cpp_value(return_type)

        methods.append(f"    // IDS Path: {path}")
        methods.append(f"    virtual {return_type} {func_name}{args_def} {{")
        methods.append(f"        // TODO: User implementation to fetch real data.")
        methods.append(f"        return {default_value};")
        methods.append(f"    }}\n")
    return "\n".join(methods)


def generate_body_recursive(node, json_var, indices, indent):
    """Recursively generates the C++ body of the main 'generate' method."""
    code = []
    indent_str = "    " * indent

    for child_name, child_node in sorted(node.children.items()):
        if child_name == '_array_element_':
            # Parent node (node) is a DIMENSION, e.g., 'flux_loop'
            dim_path = node.ids_path
            size_func_name, _ = map_path_to_cpp_parts(dim_path)
            call_args = ", ".join(indices)
            
            index_var = f"idx_{len(indices)}"
            # Make the size variable name unique by using the full path to avoid redeclaration.
            clean_path_for_var = dim_path.replace('[#]', '').replace('/', '_')
            size_var = f"size_{clean_path_for_var}"

            code.append(f'{indent_str}size_t {size_var} = {size_func_name}({call_args});')
            code.append(f'{indent_str}for (size_t {index_var} = 0; {index_var} < {size_var}; ++{index_var}) {{')
            
            new_json_var = f'{json_var}[{index_var}]'
            new_indices = indices + [index_var]
            code.extend(generate_body_recursive(child_node, new_json_var, new_indices, indent + 1))
            
            code.append(f'{indent_str}}}')
        else:
            # This is a regular field or a struct
            is_data_source = False
            if child_node.mapping_info:
                map_type = child_node.mapping_info.get("map_type", child_node.mapping_info.get("MAP_TYPE"))
                if map_type == "DATA_SOURCE":
                    is_data_source = True

            if is_data_source:  # It's a leaf node (DATA_SOURCE)
                getter_func_name, _ = map_path_to_cpp_parts(child_node.ids_path)
                call_args = ", ".join(indices)
                code.append(f'{indent_str}{json_var}["{child_name}"] = {getter_func_name}({call_args});')
            else:  # It's a struct node or an array container (DIMENSION)
                new_json_var = f'{json_var}["{child_name}"]'
                code.extend(generate_body_recursive(child_node, new_json_var, indices, indent))
    return code


def generate_writer(ids_name, structures_file, mapping_file, output_file):
    """Main function to generate the C++ writer header file."""
    
    print("Loading structures...")
    structures_map = load_structures(ids_name, structures_file)
    
    print("Loading mappings...")
    with open(mapping_file, 'r') as f:
        mappings = json.load(f)

    print("Building IDS hierarchy tree...")
    tree = build_tree(mappings)

    class_name = f"{ids_name.capitalize()}JsonWriter"
    
    print(f"Generating C++ code for class '{class_name}'...")
    
    # Generate the virtual methods for the user to implement
    protected_methods_code = generate_protected_methods(mappings, ids_name, structures_map)
    
    # Generate the body of the main `generate` method
    generate_method_body = generate_body_recursive(tree, "root", [], 3)

    cpp_code = f"""#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include "NDData.hpp"

/**
 * Auto-generated base class for writing {ids_name} data to JSON.
 *
 * To use this, create a derived class and override the protected virtual methods
 * to provide real data.
 *
 * Example:
 *
 * class My{class_name} : public {class_name} {{
 * protected:
 *     size_t get_flux_loop() override {{
 *         // Return actual size of flux_loop array
 *         return 3;
 *     }}
 *
 *     std::string get_flux_loop_name(size_t idx_0) override {{
 *         // Return actual name for flux_loop at index idx_0
 *         return "real_name_" + std::to_string(idx_0);
 *     }}
 *     // ... override other methods
 * }};
 *
 */
class {class_name}
{{
public:
    virtual ~{class_name}() = default;

    nlohmann::json generate(int shot)
    {{
        nlohmann::json root;

{chr(10).join(generate_method_body)}

        return root;
    }}

protected:
{protected_methods_code}
}};
"""

    with open(output_file, 'w') as f:
        f.write(cpp_code)
    
    print(f"Successfully generated C++ writer header file at '{output_file}'")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a C++ base class for writing an IDS to a JSON file.")
    parser.add_argument("ids_name", type=str, help="Name of the IDS (e.g., 'magnetics').")
    parser.add_argument("structures_file", type=str, help="Path to the Python structures file (e.g., 'magnetics_structures.py') or its directory.")
    parser.add_argument("mapping_file", type=str, help="Path to the JSON mapping file (e.g., 'magnetics_mapping.json').")
    parser.add_argument("-o", "--output", dest="output_file", help="Path for the output C++ header file. Defaults to '<ids_name>_writer.hpp'.")
    
    args = parser.parse_args()
    
    output_file = args.output_file
    if not output_file:
        output_file = f"{args.ids_name}_writer.hpp"
        
    generate_writer(args.ids_name, args.structures_file, args.mapping_file, output_file)