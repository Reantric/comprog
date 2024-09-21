import math
import subprocess
from collections import defaultdict
import os
import time
from colorama import Fore, Style, init

# Initialize colorama
init(autoreset=True)

# Initialize dictionaries to hold input and answer file names
inp = defaultdict()
ans = defaultdict()

def run_tests(directory, suite_name):
    # List all files in the given directory
    print(f"{Fore.MAGENTA}Running tests on the {suite_name} suite...")
    #print(os.listdir(directory))
    time.sleep(1)
    inp.clear()
    ans.clear()
    for x in os.listdir(directory):
        if x.endswith(".in"):
            x += "-"
            inp[int(x[:min(x.index("."), x.index("-"))])] = x[:-1]
        elif x.endswith(".ans"):
            x += "-"
            ans[int(x[:min(x.index("."), x.index("-"))])] = x[:-1]

    # Number of test cases
    n = len(inp)

    # Time limit (ms)
    TL = 4000

    # Initialize max test time
    maxTestTime = 0
    # Flag for all tests passing
    tests = True

    # Define the verify function
    def verify(user_output, jury_output):
        return user_output == jury_output
        #user_output = float(''.join(user_output))
       # jury_output = float(''.join(jury_output))
        #absolute_error = abs(user_output - jury_output)
       # relative_error = absolute_error / abs(jury_output) if jury_output != 0 else float('inf')
       # return absolute_error <= 10 ** -6 or relative_error <= 10 ** -6

    # Iterate over each test case
    for x in range(n):
        # Read the jury output
        jury = ""
        with open(f"{directory}/{ans[x + 1]}", mode='r') as f:
            jury = f.read().strip().splitlines()

        # Read the input
        soln = ""
        with open(f"{directory}/{inp[x + 1]}", mode='r') as f:
            ip = f.read()

            start_time = time.time()
            result = subprocess.run("cmake-build-debug/cf", input=ip, text=True, capture_output=True)
            mxt = time.time() - start_time
            mxt *= 1000
            maxTestTime = max(maxTestTime, mxt)
            print(f"--- Test {x + 1}: {mxt} milliseconds ---")

            soln = result.stdout.strip().splitlines()

        # Verify the solution against the jury's output
        if verify(soln, jury):
            print(f"{Fore.GREEN if mxt <= TL else Fore.YELLOW}Test {x + 1} Passed")
        else:
            print(f"{Fore.RED}Test {x + 1} Failed, Expected {jury}, got {soln}")
            #print('\n'.join(soln))
            tests = False

    # Final result summary
    if tests:
        if maxTestTime < TL:
            print(f"{Fore.GREEN}All test cases passed in max {math.ceil(maxTestTime)} ms!")
            return True
        else:
            print(f"{Fore.YELLOW}It's right but too goddang slow!? {round((maxTestTime-TL)/1000,2)} sec too slow...")
            return False
    else:
        print(f"{Fore.RED}Oh no, it failed somewhere at least once")
        return False

# Run tests on the sample suite
if run_tests("custom_tester/sample", "sample"):
    # Wait 2 seconds before running the secret suite
    time.sleep(2)
    # Run tests on the secret suite
    run_tests("custom_tester/secret", "secret")


##
#--- Test 21: 24187.842845916748 milliseconds ---
#Test 21 Passed
#--- Test 22: 49069.98014450073 milliseconds ---
#Test 22 Passed
#--- Test 23: 12551.954984664917 milliseconds ---
#Test 23 Passed
#--- Test 24: 3218.5871601104736 milliseconds ---