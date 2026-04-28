#!/usr/bin/env python3
import argparse
import importlib.util
import json
import os
import re
import sys
import random

# Configuration for dummy data generation
DUMMY_ARRAY_SIZE = 2  # Size for {{ #n }} placeholders
LEAF_ARRAY_SIZE = 10  # Size for leaf arrays (rank > 0)

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
    
    # Convert list of structures to a dict for easy lookup
    return {s.name: s for s in module.structures}

def get_field_info(ids_path, root_struct_name, structures_map):
    """
    Resolves the type and rank of a field given its IDS path (e.g., 'flux_loop[#]/name').
    Returns a tuple (type_name, rank).
    """
    # Clean up path: remove [n] or [#]
    clean_path = re.sub(r'\[.*?\]', '', ids_path)
    tokens = clean_path.split('/')
    
    current_struct_name = root_struct_name
    
    # Handle the case where the root structure name in the file might have a suffix like "_struct"
    # or might match the IDS name exactly.
    if current_struct_name not in structures_map:
         if f"{current_struct_name}_struct" in structures_map:
             current_struct_name = f"{current_struct_name}_struct"

    for i, token in enumerate(tokens):
        if current_struct_name not in structures_map:
            # If we can't find the structure, we can't determine the type.
            # This might happen if the path goes into a primitive type or unknown struct.
            return "unknown", 0
            
        struct = structures_map[current_struct_name]
        
        # Find the field in the current structure
        field = next((f for f in struct.fields if f.name == token or f.name == f"{token}_vect"), None)
        
        if field is None:
            return "unknown", 0
        
        if i == len(tokens) - 1:
            # We reached the leaf
            return field.type_name, field.rank
        
        # Navigate down
        # If it's a vector of structs, the type name usually looks like "std::vector<flux_loop_struct>"
        # We need to extract "flux_loop_struct"
        if field.is_vector or field.is_struct:
            type_name = field.type_name
            if "std::vector" in type_name:
                match = re.search(r'<(\w+)>', type_name)
                if match:
                    current_struct_name = match.group(1)
                else:
                    return "unknown", 0
            else:
                current_struct_name = type_name
                # Remove pointer * if present (though python structs usually don't have them in names)
                current_struct_name = current_struct_name.replace('*', '')
        else:
            # Path continues but field is not a struct? Should not happen for valid paths.
            return "unknown", 0
            
    return "unknown", 0

def generate_value(type_name, rank):
    """Generates a dummy value based on C++ type name and rank."""
    
    def get_scalar(t_name):
        if t_name in ["double", "float"]:
            return round(random.uniform(0.0, 100.0), 4)
        elif t_name in ["int", "unsigned int", "short", "long"]:
            return random.randint(0, 100)
        elif t_name == "std::string":
            return "dummy_string"
        return 0

    if rank == 0:
        return get_scalar(type_name)
    elif rank == 1:
        return [get_scalar(type_name) for _ in range(LEAF_ARRAY_SIZE)]
    elif rank == 2:
        return [[get_scalar(type_name) for _ in range(LEAF_ARRAY_SIZE)] for _ in range(LEAF_ARRAY_SIZE)]
    
    return None

def set_value_in_json(data, path_tokens, value):
    """
    Sets a value in a nested dictionary/list structure given a list of path tokens.
    Creates intermediate lists or dictionaries as needed.
    This version is robust against path conflicts by overwriting scalar values with containers.
    Numeric tokens imply lists.
    """
    current = data
    for i, token in enumerate(path_tokens[:-1]):
        is_index = token.isdigit()
        next_token = path_tokens[i+1]
        next_is_index = next_token.isdigit()

        if is_index:
            index = int(token)
            # This should not happen if the logic works, but as a safeguard:
            if not isinstance(current, list):
                return

            while len(current) <= index:
                current.append(None)

            # If the target is a scalar or None, we need to replace it with a container.
            if not isinstance(current[index], (dict, list)):
                current[index] = [] if next_is_index else {}

            current = current[index]
        else:  # token is a key
            # This should not happen if the logic works, but as a safeguard:
            if not isinstance(current, dict):
                return

            # If the key doesn't exist, or if it exists but is not a container, overwrite it.
            if token not in current or not isinstance(current.get(token), (dict, list)):
                current[token] = [] if next_is_index else {}
            current = current[token]

    # Set the leaf value
    last_token = path_tokens[-1]
    if last_token.isdigit():
        index = int(last_token)
        if not isinstance(current, list): return
        while len(current) <= index:
            current.append(None)
        current[index] = value
    else:
        if not isinstance(current, dict): return
        current[last_token] = value

def expand_placeholders(signal_path, value):
    """
    Expands {{ #n }} placeholders in the signal path.
    Returns a list of (resolved_path, value) tuples.
    Since we are generating dummy data, we just replicate the value for indices 0..DUMMY_ARRAY_SIZE-1.
    """
    # Find all placeholders like {{ #0 }}, {{ #1 }}
    placeholders = re.findall(r'\{\{\s*#(\d+)\s*\}\}', signal_path)
    
    if not placeholders:
        return [(signal_path, value)]
    
    # We simply generate paths for indices 0 to DUMMY_ARRAY_SIZE-1 for each placeholder.
    # For simplicity, we'll just do a simple replacement for now.
    # If there are multiple placeholders, this simple loop handles them sequentially 
    # but ideally we should do a cartesian product. 
    # For this dummy generator, let's assume we just want to populate index 0 and 1 for all dimensions.
    
    paths = [signal_path]
    
    for ph in set(placeholders): # unique placeholders
        new_paths = []
        for p in paths:
            for i in range(DUMMY_ARRAY_SIZE):
                # Replace {{ #n }} with i
                # We use a specific regex for the current placeholder index
                pattern = r'\{\{\s*#' + ph + r'\s*\}\}'
                resolved = re.sub(pattern, str(i), p)
                new_paths.append(resolved)
        paths = new_paths
        
    return [(p, value) for p in paths]

def generate_data(ids_name, structures_file, mapping_file, output_file):
    structures_map = load_structures(ids_name, structures_file)
    
    with open(mapping_file, 'r') as f:
        mappings = json.load(f)
        
    data = {}
    
    for ids_path, mapping in mappings.items():
        # We only care about JSON data sources for generating the JSON data file
        if not isinstance(mapping, dict):
            continue

        # Ignore internal mappings (starting with '_') which are used for probes
        # and do not represent final data structure leaves.
        if ids_path.startswith('_'):
            continue
        
        if mapping.get("MAP_TYPE") == "DATA_SOURCE" and mapping.get("DATA_SOURCE") == "JSON":
            signal = mapping.get("ARGS", {}).get("signal")
            if not signal:
                continue
            
            # Determine type and rank from structures
            type_name, rank = get_field_info(ids_path, ids_name, structures_map)
            
            # Generate a dummy value
            dummy_value = generate_value(type_name, rank)
            
            # Expand placeholders in signal path (e.g. {{ #0 }} -> 0, 1)
            # and insert into data dict
            expanded_entries = expand_placeholders(signal, dummy_value)
            
            for resolved_path, val in expanded_entries:
                # Split path into tokens for insertion
                # Remove empty strings from split (e.g. leading /)
                tokens = [t for t in resolved_path.split('/') if t]
                set_value_in_json(data, tokens, val)

    # Write to output file
    with open(output_file, 'w') as f:
        json.dump(data, f, indent=2)
    
    print(f"Successfully generated dummy data in '{output_file}'")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate dummy JSON data based on mappings and structures.")
    parser.add_argument("ids_name", type=str, help="Name of the IDS (e.g., magnetics)")
    parser.add_argument("structures_file", type=str, help="Path to the structures.py file or directory")
    parser.add_argument("mapping_file", type=str, help="Path to the mappings.json file")
    parser.add_argument("-o", "--output", dest="output_file", default="data_dummy.json", help="Output JSON data file")
    
    args = parser.parse_args()
    
    generate_data(args.ids_name, args.structures_file, args.mapping_file, args.output_file)