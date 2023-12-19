# gen -sum-n 50 -min-value 2 -max-value 3 -value-bias 6 > $
from random import randint, random

for x in range(20):
    s = randint(1, 10)
    mi = randint(-10, 10)
    ma = randint(-10, 10)
    if mi > ma:
        mi, ma = ma, mi
    v = randint(-1,1)
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")


for x in range(10):
    s = randint(101, 1000)
    mi = randint(2,100)
    ma = randint(2,100)
    if mi > ma:
        mi, ma = ma, mi
    v = randint(-1,1)
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")

for x in range(10):
    s = randint(101, 1000)
    mi = randint(2,100000)
    ma = randint(2,100000)
    if mi > ma:
        mi, ma = ma, mi
    v = randint(-2,2)
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")


for x in range(10):
    s = randint(101, 1000)
    mi = randint(-100000,100000)
    ma = randint(-100000,100000)
    if mi > ma:
        mi, ma = ma, mi
    v = randint(-3,3)
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")


for x in range(10):
    s = randint(1000, 10000)
    mi = randint(-1000000,1000000)
    ma = randint(-1000000,1000000)
    if mi > ma:
        mi, ma = ma, mi
    v = randint(-4,4)
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")


for x in range(50):
    s = randint(10000, 100000)
    mi = randint(-100000000,100000000)
    ma = randint(-100000000,100000000)
    if mi > ma:
        mi, ma = ma, mi
    v = randint(-8,8)
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")

for x in range(16):
    s = 100000
    mi = -10**9
    ma = -1
    if mi > ma:
        mi, ma = ma, mi
    v = x-8
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")

for x in range(50):
    s = 100000
    mi = -10**9
    ma = 10**9
    if mi > ma:
        mi, ma = ma, mi
    v = x-24
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")
