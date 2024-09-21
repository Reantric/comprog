import math
import subprocess
from collections import defaultdict
import os
import time
from colorama import Fore, Style, init

# Initialize colorama (optional, if you plan to use colored output)
init()

# Read input from "me.in"
with open("me.in", mode='r') as f:
    ip = f.read()

    # Start timing the subprocess execution
    start_time = time.time()
    result = subprocess.run(
        ["cmake-build-debug/cf"],  # It's better to pass the command as a list
        input=ip,
        text=True,
        capture_output=True
    )
    elapsed_time = (time.time() - start_time) * 1000  # Convert to milliseconds

    # Prepare the output content
    soln = result.stdout.strip().splitlines()
    print(f"--- Test: {elapsed_time:.2f} milliseconds ---")
    output_content = "\n".join(soln)

# Write the output to "me.out"
with open("me.out", mode='w') as out_file:
    out_file.write(output_content)

# Optional: Print a confirmation message (can be removed if not needed)
print("Output has been written to me.out")
