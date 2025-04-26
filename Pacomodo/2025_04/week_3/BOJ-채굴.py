# 15573번 채굴
# 파라메트릭
import sys
input = sys.stdin.readline
from collections import deque

def mining(mine, N, M, K, D):
    total = 0
    dr, dc = [-1, 1, 0, 0], [0, 0, -1, 1]
    visited = [[0 for _ in range(M)] for _ in range(N)]
    queue = deque()
    for i in range(M):
        if mine[0][i] <= D:
            queue.append((0, i))
            visited[0][i] = 1
            total += 1
    for i in range(1, N):
        if mine[i][0] <= D:
            queue.append((i, 0))
            visited[i][0] = 1
            total += 1
        if mine[i][M-1] <= D:
            queue.append((i, M-1))
            visited[i][M-1] = 1
            total += 1
    while queue:
        row, col = queue.popleft()
        for i in range(4):
            now_r, now_c = row+dr[i], col+dc[i]
            if 0 <= now_r < N and 0 <= now_c < M:
                if mine[now_r][now_c] <= D and visited[now_r][now_c] == 0:
                    visited[now_r][now_c] = 1
                    total += 1
                    queue.append((now_r, now_c))
    if K <= total:
        return True
    else:
        return False

def parametric(judge, mine, N, M, K):
    start, end = 0, max(max(mine[i]) for i in range(N))
    while start < end:
        D = (start + end)//2
        if judge(mine, N, M, K, D) == False:
            start = D + 1
        else:
            end = D
    return end

def main():
    N, M, K = map(int, input().rstrip().split())
    mine = [list(map(int, input().rstrip().split())) for _ in range(N)]
    print(parametric(mining, mine, N, M, K))

main()