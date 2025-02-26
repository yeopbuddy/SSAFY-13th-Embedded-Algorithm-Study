# from itertools import combinations as c
from itertools import permutations as p

n, m, k = map(int, input().split())
a = list(map(int, input().split()))
_a = list(p(a, n))
mbag = 1e9
for __a in _a:
    bagidx = 0
    bag = 0
    bagcnt = 0
    baglst = []
    while(True):
        if (bag + __a[bagidx] <= m):
            bag += __a[bagidx]
        else:
            bagcnt += 1
            baglst.append(bag)
            if(bagcnt == k):
                if(mbag > sum(baglst)):
                    mbag = sum(baglst)
                break
            bag = __a[bagidx]
        bagidx += 1
        bagidx %= n
print(mbag)