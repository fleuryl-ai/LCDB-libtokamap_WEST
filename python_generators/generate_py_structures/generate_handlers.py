#!/usr/bin/env python3
import argparse
import importlib.util
import json
import os
import re
import sys

def load_structures(ids_name, structures_file):
    """Loads the structures module dynamically."""
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
    """Resolves the type of a field given its IDS path to provide a better default value."""
    # Handle internal paths starting with _ (dimensions)
    if ids_path.startswith('_'):
        return "int", False # Dimensions are usually integers

    clean_path = re.sub(r'\[.*?\]', '', ids_path)
    tokens = clean_path.split('/')
    
    current_struct_name = root_struct_name
    if current_struct_name not in structures_map and f"{current_struct_name}_struct" in structures_map:
        current_struct_name = f"{current_struct_name}_struct"

    for i, token in enumerate(tokens):
        if current_struct_name not in structures_map: return "unknown", False
        struct = structures_map[current_struct_name]
        field = next((f for f in struct.fields if f.name == token or f.name == f"{token}_vect"), None)
        if field is None: return "unknown", False
        if i == len(tokens) - 1:
            if field.is_vector and field.is_struct:
                return "int", False
            # An array can be a std::vector of structs (is_vector) or a C-style array of primitives (is_array, e.g. for FLT_1D)
            return field.type_name, field.is_array or field.is_vector
        
        if field.is_vector or field.is_struct:
            type_name = field.type_name
            if "std::vector" in type_name:
                match = re.search(r'<(\w+)>', type_name)
                current_struct_name = match.group(1) if match else "unknown"
            else:
                current_struct_name = type_name.replace('*', '')
        else:
            return "unknown", False
    return "unknown", False

def get_default_return_value(py_type):
    """Returns a C++ string representing a default TypedDataArray value."""
    if "string" in py_type: return 'libtokamap::TypedDataArray{std::string{""}}'
    if "float" in py_type or "double" in py_type: return 'libtokamap::TypedDataArray{0.0}'
    if "int" in py_type: return 'libtokamap::TypedDataArray{0}'
    return 'libtokamap::TypedDataArray{0}'

def map_path_to_function_name(path):
    """Converts an IDS path (e.g. flux_loop[#]/name) to a C++ function name (get_flux_loop_name)."""
    # Remove [n] or [#] and replace / with _
    clean = re.sub(r'\[.*?\]', '', path)
    clean = clean.replace('/', '_')
    # Remove leading underscore if present (for dimensions)
    if clean.startswith('_'):
        clean = clean[1:]
    return f"get_{clean}"

def extract_user_code(file_path):
    """Extracts user-defined code blocks from an existing file with metadata."""
    user_blocks = {}
    if not os.path.exists(file_path):
        return user_blocks

    with open(file_path, 'r') as f:
        content = f.read()

    # Symmetrical pattern: matches // BEGIN USER CODE: <tag> ... // END USER CODE: <tag>
    # The <tag> can be "[func_name] [Path: ...] [Version: ...]" or just "func_name"
    pattern = r'// BEGIN USER CODE: (?P<tag>.*?) *\n(?P<code>.*?)\n\s*// END USER CODE: (?P=tag)'
    matches = re.finditer(pattern, content, re.DOTALL)
    for match in matches:
        tag = match.group('tag').strip()
        code = match.group('code')
        
        # Extract function name and version from the tag
        # Try bracketed format first: [name] [Path: ...] [Version: ...]
        name_match = re.search(r'^\[([\w\d_]+)\]', tag)
        if name_match:
            func_name = name_match.group(1)
            version_match = re.search(r'\[Version: ([\w\d._+-]+)\]', tag)
            version = version_match.group(1) if version_match else "unknown"
        else:
            # Fallback to simple format: name
            func_name = tag.split()[0]
            version = "unknown"
            
        user_blocks[func_name] = {"code": code, "version": version}
    
    return user_blocks

def generate_handlers(ids_name, structures_file, mapping_file, output_file, schema_version):
    print(f"Reading existing user code from {output_file}...")
    user_blocks = extract_user_code(output_file)

    print("Loading structures...")
    structures_map = load_structures(ids_name, structures_file)
    
    print("Loading mappings...")
    with open(mapping_file, 'r') as f:
        mappings = json.load(f)

    functions = []
    dispatcher_entries = []

    print(f"Generating handlers for IDS version: {schema_version}...")
    for path, info in sorted(mappings.items()):
        if not isinstance(info, dict):
            continue
            
        map_type = info.get("map_type", info.get("MAP_TYPE"))
        data_source = info.get("DATA_SOURCE")
        
        if data_source != "WEST":
            if map_type == "DIMENSION":
                continue
            if map_type != "DATA_SOURCE":
                continue

        func_name = map_path_to_function_name(path)
        py_type, is_array = get_field_info(path, ids_name, structures_map)
        
        base_type = py_type
        if "std::vector" in base_type:
            match = re.search(r'<([\w: ]+)>', base_type)
            if match: base_type = match.group(1)
        base_type = base_type.replace('*', '')

        # Check if we have existing user code for this function
        existing_data = user_blocks.get(func_name)
        
        tag_id = f"[{func_name}] [Path: {path}] [Version: {schema_version}]"
        
        if existing_data:
            user_code = existing_data["code"]
            old_version = existing_data["version"]
            
            # Migration logic
            if old_version != schema_version and old_version != "unknown":
                if f"MIGRATED FROM {old_version}" not in user_code:
                    user_code = f"    // MIGRATED FROM {old_version}\n" + user_code
            
            func_body = f"    // BEGIN USER CODE: {tag_id}\n{user_code}\n    // END USER CODE: {tag_id}"
        else:
            # Default implementation
            if is_array:
                func_body = f"""    // BEGIN USER CODE: {tag_id}
    // TODO: Implement logic for {path}
    // Example: int idx0 = indices[0];

    // Prepare buffer for {base_type} (1D to 6D)
    std::vector<size_t> shape = {{1}}; // TODO: Set dimensions
    size_t size = 1; // TODO: Calculate total size
    // for (auto dim : shape) size *= dim;

    auto* buffer = new {base_type}[size];

    // TODO: Fill buffer
    // buffer[0] = ...;

    return libtokamap::TypedDataArray(buffer, size, shape);
    // END USER CODE: {tag_id}"""
            else:
                default_val = get_default_return_value(py_type)
                func_body = f"""    // BEGIN USER CODE: {tag_id}
    // TODO: Implement logic for {path}
    // Example: int idx0 = indices[0];
    return {default_val};
    // END USER CODE: {tag_id}"""

        func_code = f"""libtokamap::TypedDataArray {func_name}(const libtokamap::DataSourceArgs& args, const libtokamap::MapArguments& arguments, const std::vector<int>& indices)
{{
{func_body}
}}"""
        
        functions.append(func_code)
        dispatcher_entries.append(f'    {{"{func_name}", {func_name}}}')

    content = f"""// Auto-generated handlers for WESTDataSource
// Generated by generate_handlers.py
// IDS Version: {schema_version}

#include <libtokamap.hpp>
#include <string>
#include <unordered_map>
#include <vector>

// Definition of the function pointer type for handlers
using SignalHandler = libtokamap::TypedDataArray (*)(const libtokamap::DataSourceArgs&, const libtokamap::MapArguments& arguments, const std::vector<int>&);

// Function Stubs
"""
    content += "\n\n".join(functions)
    
    content += """

// Dispatcher Map
const std::unordered_map<std::string, SignalHandler> signal_dispatcher = {
"""
    content += ",\n".join(dispatcher_entries)
    content += "\n};\n"

    with open(output_file, 'w') as f:
        f.write(content)
    
    print(f"Successfully generated handlers in '{output_file}'")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate C++ handler stubs and dispatcher map for WESTDataSource.")
    parser.add_argument("ids_name", type=str, help="Name of the IDS (e.g., 'magnetics').")
    parser.add_argument("structures_file", type=str, help="Path to the Python structures file.")
    parser.add_argument("mapping_file", type=str, help="Path to the JSON mapping file.")
    parser.add_argument("-o", "--output", dest="output_file", help="Output C++ file. Defaults to 'west_<ids_name>_handlers.cpp'.")
    parser.add_argument("--schema-version", dest="schema_version", default="unknown", help="Version of the IDS schema.")
    
    args = parser.parse_args()

    output_file = args.output_file
    if not output_file:
        output_file = f"west_{args.ids_name}_handlers.cpp"

    generate_handlers(args.ids_name, args.structures_file, args.mapping_file, output_file, args.schema_version)