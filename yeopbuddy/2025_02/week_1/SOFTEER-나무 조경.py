import sys
from itertools import combinations as c
n = int(input())
_map = [list(map(int, input().split())) for _ in range(n)]
m = []
count = 1
for i in range(n):
    for j in range(n):
        if i == n-1:
            if j == n-1:
                break
            else:
                m.append([count, count + 1, _map[i][j]+_map[i][j+1]])
        else:
            if j == n-1:
                m.append([count, count + n, _map[i][j]+_map[i+1][j]])
            else:
                m.append([count, count + 1, _map[i][j]+_map[i][j+1]])
                m.append([count, count + n, _map[i][j]+_map[i+1][j]])
        count += 1
if n == 2:
    print(_map[0][0] + _map[0][1] + _map[1][0] + _map[1][1])
else:
    hy = list(c(m, 4))
    hset = set()
    for h in hy:
        if len(list(set(h[0][:2] + h[1][:2] + h[2][:2] + h[3][:2]))) == 8:
            #print(h)
            hset.add(h[0][2]+h[1][2]+h[2][2]+h[3][2])
            #print(h[0][3]+h[1][3]+h[2][3]+h[3][3])
    print(max(list(hset)))