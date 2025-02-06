import sys

n, m = map(int, input().split())
SDB = list(map(int, input().split()))
CONNECTION = {i : [] for i in range(n)}
for _ in range(m):
    n1, n2 = map(int, input().split())
    CONNECTION[n1-1].append(n2-1)
    CONNECTION[n2-1].append(n1-1)
ANS = 0
for k, v in CONNECTION.items():
    HARDER = True
    for val in v:
        if SDB[val] >= SDB[k]:
            HARDER = False
            break
    if(HARDER):
        ANS += 1
print(ANS)        