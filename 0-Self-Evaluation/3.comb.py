import itertools
import numpy as np

def comb(n, k, m = 1):
    if k <= 0:
        return [[]]
    if n - m + 1 == k:
        return [list(range(m, n + 1))]
    else:
        ans = []
        for x in range(m, n - (k - 1) + 1):
            old = comb(n, k - 1, x + 1)
            for line in old: 
                line.insert(0, x)
            ans += old
        return ans

print(len(comb(6, 3)))
print(len(list(itertools.combinations(list(range(1, 7)), 3))))

