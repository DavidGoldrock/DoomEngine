import re

def generate_cpp_constructor(struct_definition):
    # Extract the struct name
    struct_name_match = re.search(r'struct\s+(\w+)\s*{', struct_definition)
    if not struct_name_match:
        raise ValueError("Struct name not found in the definition")
    struct_name = struct_name_match.group(1)
    
    # Extract member variables
    member_lines = re.findall(r'\s*(\w+)\s+(\w+);', struct_definition)
    
    # Generate the constructor arguments
    constructor_args = []
    for type_, name in member_lines:
        constructor_args.append(f"{type_} {name}")
    
    # Generate the initializer list
    initializer_list = []
    for type_, name in member_lines:
        initializer_list.append(f"{name}({name})")

    # Format the constructor
    constructor_code = (
        f"// Constructor\n"
        f"    {struct_name}({', '.join(constructor_args)})\n"
        f"        : {', '.join(initializer_list)}\n"
        f"    {{}}\n"
    )
    
    return constructor_code

def generate_cpp_stream_operator(struct_definition):
    # Extract the struct name
    struct_name_match = re.search(r'struct\s+(\w+)\s*{', struct_definition)
    if not struct_name_match:
        raise ValueError("Struct name not found in the definition")
    struct_name = struct_name_match.group(1)
    
    # Extract member variables
    member_lines = re.findall(r'\s*(\w+)\s+(\w+);', struct_definition)
    
    # Generate the stream operator code
    stream_operator_lines = []
    for type_, name in member_lines:
        # Handle special characters in names (e.g., spaces or quotes)
        clean_name = name.replace('"', '\\"')
        stream_operator_lines.append(f'    os << "{name}: " << obj.{name} << " ";')
    
    # Format the stream operator
    seperator = '\n'
    stream_operator_code = f"""
#include <iostream>

friend std::ostream& operator<<(std::ostream& os, const {struct_name}& obj) {{
    os << "{struct_name}{{ ";
    {seperator.join(stream_operator_lines)}
    os << "}}";
    return os;
}}
"""
    
    return stream_operator_code

def mlinput():
    lines = ""
    while True:
        try:
            line = input()
        except EOFError:
            break
        if line == "":
            return lines
        lines += line + "\n"

print("Enter/Paste your content. Ctrl-D or Ctrl-Z ( windows ) to save")

while True:
    print(generate_cpp_stream_operator(mlinput()))