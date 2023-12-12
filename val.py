import subprocess

# Replace 'program.cpp' with the path to your C++ file.
cpp_source_path = 'custom_tester/output_validator/outputValidator.cpp'
# Replace 'program' with the desired name of the compiled executable.
cpp_executable_path = 'happy'

# Compile the C++ program.
compilation = subprocess.run(['g++', '-std=c++20', '-o', cpp_executable_path, cpp_source_path], capture_output=True, text=True)
if compilation.returncode != 0:
    # If there's an error during compilation, print it out.
    print("Compilation failed with errors:")
    print(compilation.stderr)
else:
    print("Compilation successful.")
