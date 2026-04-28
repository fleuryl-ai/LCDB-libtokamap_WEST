#!/usr/bin/env python3
import argparse
import importlib.util
import json
import os
import re
import sys
from collections import OrderedDict

# This script generates a mappings.json file for a given IDS,
# based on its Python structure definition, for the JSON data source.

def convert_to_signal_path(map_path):
    """
    Converts a mapping path with placeholders like '[#]' to a signal path
    with Inja-style placeholders like '{{ #0 }}'.
    Example:
        'flux_loop[#]/position[#]/r' -> 'flux_loop/{{ #0 }}/position/{{ #1 }}/r'
    """
    i = 0
    def repl(match):
        nonlocal i
        res = f"/{{{{ #{i} }}}}"
        i += 1
        return res

    # Replace each '[#]' with '/{{ #i }}/'
    signal_path = re.sub(r'\[#\]', repl, map_path)
    return signal_path

def generate_mappings_recursive(structure, all_structures_map, path_prefix, mappings, data_source_name):
    """
    Recursively traverses the IDS structure and generates the corresponding mappings.
    """
    for field in structure.fields:
        # Per user request, vector fields like 'flux_loop_vect' are mapped to 'flux_loop'
        field_map_name = field.name
        if field.is_vector and field_map_name.endswith('_vect'):
             field_map_name = field_map_name[:-5] # remove '_vect'
        
        current_map_path = path_prefix + field_map_name

        if field.is_vector:
            # For a vector of structures (struct_array)

            # Map the array name itself to a handler that returns the size.
            mappings[current_map_path] = {
                "MAP_TYPE": "DATA_SOURCE",
                "DATA_SOURCE": data_source_name,
                "ARGS": {"signal": convert_to_signal_path(current_map_path)}
            }

            # 3. Recurse into the structure within the vector.
            # The type name is like 'std::vector<flux_loop_struct>'. We need 'flux_loop_struct'.
            match = re.search(r'<(\w+)>', field.type_name)
            if not match:
                continue
            
            inner_struct_name = match.group(1)
            if inner_struct_name in all_structures_map:
                inner_structure = all_structures_map[inner_struct_name]
                # The new path prefix for items inside the array is '...[#]/'
                new_path_prefix = f"{current_map_path}[#]/"
                generate_mappings_recursive(inner_structure, all_structures_map, new_path_prefix, mappings, data_source_name)

        elif field.is_struct:
            # For a nested structure that is not a vector.
            # The type name is like 'ids_properties_struct'.
            inner_struct_name = field.type_name
            if inner_struct_name in all_structures_map:
                inner_structure = all_structures_map[inner_struct_name]
                # The new path prefix is '.../field_name/'
                new_path_prefix = f"{current_map_path}/"
                generate_mappings_recursive(inner_structure, all_structures_map, new_path_prefix, mappings, data_source_name)

        else:
            # For a simple, non-structural field.
            mappings[current_map_path] = {
                "MAP_TYPE": "DATA_SOURCE",
                "DATA_SOURCE": data_source_name,
                "ARGS": {"signal": convert_to_signal_path(current_map_path)}
            }

def generate_mappings(ids_name: str, structures_py_path: str, output_file: str, data_source_name: str):
    """
    Main function to generate the mappings.json file.
    """
    # If the provided path is a directory, construct the full file path
    # by assuming the file is named after the IDS.
    if os.path.isdir(structures_py_path):
        structures_py_path = os.path.join(structures_py_path, f"{ids_name}_structures.py")

    try:
        spec = importlib.util.spec_from_file_location(ids_name, structures_py_path)
        if spec is None:
            print(f"Error: Could not create spec for module at '{structures_py_path}'", file=sys.stderr)
            sys.exit(1)
        structures_module = importlib.util.module_from_spec(spec)
        sys.modules[ids_name] = structures_module
        spec.loader.exec_module(structures_module)
    except FileNotFoundError:
        print(f"Error: Structures file not found at '{structures_py_path}'", file=sys.stderr)
        sys.exit(1)

    all_structures_map = {s.name: s for s in structures_module.structures}
    root_structure = all_structures_map.get(ids_name)
    if not root_structure:
        print(f"Error: Root structure '{ids_name}' not found in '{structures_py_path}'", file=sys.stderr)
        sys.exit(1)

    mappings = OrderedDict()
    mappings["version"] = "1.0.0"
    
    generate_mappings_recursive(root_structure, all_structures_map, "", mappings, data_source_name)

    with open(output_file, 'w') as f:
        json.dump(mappings, f, indent=2)
    print(f"Successfully generated '{output_file}'")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Generate a libtokamap 'mappings.json' file from an IDS python structure definition.")
    parser.add_argument("ids_name", type=str, help="The name of the IDS (e.g., 'magnetics').")
    parser.add_argument("structures_py_path", type=str, help="Path to the Python structures file (e.g., 'magnetics_structures.py').")
    parser.add_argument("-o", "--output", dest="output_file", default="mappings.json", help="Path for the output mappings.json file (default: 'mappings.json').")
    parser.add_argument("--data-source", dest="data_source", default="JSON", help="Name of the data source (default: 'JSON').")
    args = parser.parse_args()

    generate_mappings(args.ids_name, args.structures_py_path, args.output_file, args.data_source)