import sys
input = sys.stdin.readline

def dfs(index, cnt, beauty):
    global result

    if N==2:
        result = sum(map(sum, arr))
        return
    
    if cnt == 4:
        result = max(result, beauty)
        return
    if index == total_cnt:
        return

    (x, y, nx, ny, bx, bnx) = all[index]

    if not visited[x][y] and not visited[nx][ny]:
        visited[x][y], visited[nx][ny] = 1, 1
        dfs(index+1, cnt+1, beauty+bx+bnx)
        visited[x][y], visited[nx][ny] = 0, 0
    dfs(index+1, cnt, beauty)

N = int(input())
arr = [list(map(int, input().split())) for _ in range(N)]
visited = [[0]*N for _ in range(N)]
all = []
dx, dy = [0, 1, 0, -1], [1, 0, -1, 0]
for x in range(N):
    for y in range(N):
        for i in range(4):
            nx, ny = x+dx[i], y+dy[i]
            if 0<=nx<N and 0<=ny<N:
                all.append((x, y, nx, ny, arr[x][y], arr[nx][ny]))

total_cnt = len(all)

result = 0
dfs(0, 0, 0)
print(result)
