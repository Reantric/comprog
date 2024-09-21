from random import randint, sample

L = sample([x for x in range(301,302)],1)
L.sort()
for x in range(0,0):
    s = L[x]
    mi = randint(-10000000000, 10000000000)
    ma = randint(-10000000000, 10000000000)
    if mi > ma:
        mi, ma = ma, mi
    v = 0
    print(f"gen -sum-n {s} -min-value {mi} -max-value {ma} -value-bias {v} > $")

