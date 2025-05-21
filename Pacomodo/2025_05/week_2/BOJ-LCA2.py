# 11438번 LCA 2
# 트리, 최소 공통 조상, 희소 배열
import sys
input = sys.stdin.readline
from collections import deque
from math import log2, ceil

N = int(input())
graph = [[] for _ in range(N+1)]
for _ in range(N-1):
    a, b = map(int, input().rstrip().split())
    graph[a].append(b)
    graph[b].append(a)

# 최대 깊이 구하고, sparse table 초기화
sparse = [[0 for _ in range(N+1)] for _ in range(21)]
visited = [0 for _ in range(N+1)]
queue = deque()
queue.append((1, 0))
visited[1] = 1
max_depth = 0
dep = [0 for _ in range(N+1)]
while queue:
    node, depth = queue.popleft()
    for near in graph[node]:
        if visited[near] == 0:
            visited[near] = 1
            sparse[0][near] = node
            dep[near] = depth+1
            queue.append((near, depth+1))
    if depth > max_depth:
        max_depth = depth

# sparse table 구하는 과정
sparse[0][1] = 1
for i in range(1, ceil(log2(max_depth))+1):
    for j in range(1, N+1):
        sparse[i][j] = sparse[i-1][sparse[i-1][j]]

# LCA를 구하는 과정
def lca(u, v):
    if dep[u] < dep[v]:
        u, v = v, u
    if dep[u] > dep[v]:
        for i in range(20, -1, -1):
            if dep[u] - dep[v] >= (1<<i):
                u = sparse[i][u]   # 올려주자
    if u == v:
        return u
    for i in range(20, -1, -1):
        if sparse[i][u] != sparse[i][v]:
            u = sparse[i][u]
            v = sparse[i][v]

    return sparse[0][u]

M = int(input())  # 쿼리 개수
for _ in range(M):
    u, v = map(int, input().rstrip().split())
    print(lca(u, v))