import sys
input = sys.stdin.readline

def simulation():
    dp = [[[0]*2 for _ in range(N)] for _ in range(N)]

    dp[0][0][0] = grid[0][0]
    dp[0][0][1] = grid[0][0] * 2

    for i in range(N):
        dp[i][0][0] = dp[i-1][0][0] + grid[i][0]
        dp[0][i][0] = dp[0][i-1][0] + grid[0][i]

        dp[i][0][1] = max(dp[i-1][0][1] + grid[i][0], dp[i-1][0][0] + grid[i][0]*2)
        dp[0][i][1] = max(dp[0][i-1][1] + grid[0][i], dp[0][i-1][0] + grid[0][i]*2)

    for i in range(1, N):
        for j in range(1, N):
            dp[i][j][0] = max(dp[i-1][j][0], dp[i][j-1][0]) + grid[i][j]

            dp[i][j][1] = max(
                            max(dp[i-1][j][0], dp[i][j-1][0]) + grid[i][j]*2,
                            max(dp[i-1][j][1], dp[i][j-1][1]) + grid[i][j]
                             )
    return dp[N-1][N-1][1]
    
N = int(input())
grid = [list(map(int, input().split())) for _ in range(N)]

result = simulation()

print(result)