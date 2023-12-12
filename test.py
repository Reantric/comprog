import math
import subprocess
from collections import defaultdict
from math import gcd
import os
import time

inp = defaultdict()
ans = defaultdict()
print(os.listdir("custom_tester/secret"))
for x in os.listdir("custom_tester/secret"):
    if x.endswith(".in"):
        x += "-"
        inp[int(x[:min(x.index("."),x.index("-"))])] = x[:-1]
    else:
        x += "-"
        ans[int(x[:min(x.index("."),x.index("-"))])] = x[:-1]

n = 4
TL = 5000

maxTestTime = 0
tests = True
for x in range(n):
    poss = False
    l = []
    jury = ""
    with open(f"custom_tester/secret/{ans[x+1]}",mode='r') as f:
        jury = f.readlines()

        if jury[0].split()[0] == 'possible':
            poss = True
            l = int(jury[1].split()[0]),int(jury[1].split()[1])

    soln = ""
    with open(f"custom_tester/secret/{inp[x+1]}",mode='r') as f:
        ip = f.readlines()

        H = ip[0].split()
        s = f"{H[0]} {H[1]} {H[2]} {H[3]}"
        start_time = time.time()
        result = subprocess.run("cmake-build-debug/cf", input=s, text=True, capture_output=True)
        mxt = time.time() - start_time
        mxt *= 1000
        maxTestTime = max(maxTestTime,mxt)
        print("--- %s milliseconds ---" % (mxt))
        soln = result.stdout.split("\n")

    # Verif
    pos1 = False
    if soln[0] == 'possible':
        pos1 = True
    if pos1 != poss:
        print(False)
        tests = False
        break
        continue
    if soln[0] == 'possible':
        K = soln[1].split()
        k = [int(K[0]),int(K[1])]
        tests &= l[0]*k[1] == l[1]*k[0]
        print(l[0]*k[1] == l[1]*k[0])
    else:
        pass
        print(True)

if tests:
    if maxTestTime < TL:
        print(f"All test cases passed in max {math.ceil(maxTestTime)} ms!")
    else:
        print("It's right but too goddang slow!?")
else:
    print("Oh no, it failed somewhere at least once")