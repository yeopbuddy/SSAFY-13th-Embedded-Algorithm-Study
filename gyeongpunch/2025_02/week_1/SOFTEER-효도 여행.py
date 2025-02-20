from collections import defaultdict
import sys
sys.setrecursionlimit(10000)
input = sys.stdin.readline

def simulation(node, parent, dp):
    global max_happiness

    flag = True
    for neighbor, char in tree[node]:
        if neighbor != parent:
            flag = False
            new_dp = dp[:]
            for i in range(1, M+1):
                if S[i-1] == char:
                    new_dp[i] = max(new_dp[i], dp[i-1] + 1)
                new_dp[i] = max(new_dp[i], new_dp[i-1])
            simulation(neighbor, node, new_dp)

    if flag:
        max_happiness = max(max_happiness, dp[-1])

N, M = map(int, input().split())
S = input().strip()
tree = defaultdict(list)
for _ in range(N-1):
    u, v, c = input().split()
    u, v = int(u), int(v)
    tree[u].append((v, c))
    tree[v].append((u, c))

max_happiness = 0
dp = [0] * (M+1)

simulation(1, -1, dp)

print(max_happiness)
