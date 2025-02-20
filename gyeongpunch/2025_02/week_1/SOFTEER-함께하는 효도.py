from itertools import product
import sys

N, M = map(int, input().split())
arr = [list(map(int, input().split())) for _ in range(N)]

positions = []
visited = set()
value = 0

for i in range(M):
    x, y = map(lambda x : int(x) - 1, input().split())
    positions.append((x, y))
    if (x, y) not in visited:
        visited.add((x, y))
        value += arr[x][y]
        
dx, dy = [0, 1, 0, -1], [1, 0, -1, 0]

max_value = 0

def dfs(time, positions, visited, value):
    global max_value

    if time==3:
        max_value = max(max_value, value)
        return

    next_moves = []
    for x, y in positions:
        moves = []
        for i in range(4):
            nx, ny = x+dx[i], y+dy[i]
            if 0<=nx<N and 0<=ny<N:
                moves.append((nx, ny))
        next_moves.append(moves)

    for new_positions in product(*next_moves):
        if len(set(new_positions)) != len(new_positions):
            continue
        
        new_value = value
        new_visited = visited.copy()
        
        for nx, ny in new_positions:
            if (nx, ny) not in new_visited:
                new_visited.add((nx, ny))
                new_value += arr[nx][ny]

        dfs(time+1, new_positions, new_visited, new_value)

dfs(0, positions, visited, value)

print(max_value)