import sys
input = sys.stdin.readline

N, K = map(int, input().split())
data = list(map(int, input().split()))

dp = [0]*(N+1)
for i in range(1, N+1):
    dp[i] = dp[i-1] + data[i-1]

for _ in range(K):
    s, e = map(int, input().split())
    result = (dp[e] - dp[s-1]) / (e-s+1)

    print(f"{result:.2f}")
