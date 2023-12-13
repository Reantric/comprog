import math
from functools import lru_cache
from typing import List

class Person:
    def __init__(self, name, rating, place, maturity):
        self.name = name
        self.rating = rating
        self.place = place
        self.maturity = maturity

    def getName(self):
        return self.name

    def getRating(self):
        return self.rating

    def getRank(self):
        return self.place

    def getMaturity(self):
        return self.maturity

    def __repr__(self):
        return f"{self.name}: {self.rating}@{self.place}"


L: List[Person] = []
with open("rankings.in",mode='r') as f:
    for y in f.readlines():
        x = y.split()
        L.append(Person(x[0],float(x[2]),1+int(x[1]),int(x[3])))

print(L)
n = len(L)

E = [[0 for x in range(len(L))] for y in range(len(L))]

for a in range(n):
    for b in range(n):
        E[a][b] = 1/(1+10**((L[b].getRating() - L[a].getRating())/400))


ERank = [1 - E[i][i] + sum([E[j][i] for j in range(n)]) for i in range(n)]
M = [math.sqrt(ERank[i] * L[i].getRank()) for i in range(n)]

@lru_cache
def pre_sum_of_sigma(k: int) -> float:
    """
    Series cache
    :param k:
    :return:
    """
    if k < 0:
        raise ValueError(f"{k=}, pre_sum's index less than zero!")
    return (5 / 7) ** k + pre_sum_of_sigma(k - 1) if k >= 1 else 1


@lru_cache
def f(k: int) -> float:
    """
    This function could also be `return 1 / (1 + sum((5 / 7) ** i for i in range(k + 1)))`
    but use a `pre_sum_of_sigma` function(which is also cached) is faster.
    When k is big enough, result approximately equals to 2/9.
    :param k:
    :return:
    """
    return 1 / (1 + pre_sum_of_sigma(k))

def expectedRating(expectedRI, i):
    return 1 + sum([1/(1+10**(-(L[j].getRating() - expectedRI)/400)) for j in range(n) if i != j])

l = 0
r = 4000

guy = 3
c = 0
while c < 50:
    mid = (r+l)/2
    if expectedRating(mid,guy) > M[guy]:
        l = mid
    else:
        r = mid
    c += 1

newRating = (r+l)/2
Delta = f(L[guy].getMaturity())*(newRating-L[guy].getRating())

print(L[guy].getName())
print(f"Expected Rank: {ERank[guy]}")
print(f"Expected Geometric Rank: {M[guy]}")
print(f"Actual Rank: {L[guy].getRank()}")
print(f"Delta: {Delta}")
print(f"Rating before contest: {L[guy].getRating()}")
print(f"New rating: {L[guy].getRating() + Delta}")

l = 0
r = 40000
c = 0
while c < 50:
    mid = (r+l)/2
    if expectedRating(mid,guy) > L[guy].getRank():
        l = mid
    else:
        r = mid
    c += 1

print(f"! Performance rating: {(l+r)/2}")