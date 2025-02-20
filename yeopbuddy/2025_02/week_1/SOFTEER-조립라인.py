import sys
n = int(input())
line = [list(map(int, input().split())) for _ in range(n)]
if n != 1:
    for i in range(n):
        if(i == 0):
            line[i][0] = min(line[i][0], line[i][1] + line[i][3])
            line[i][1] = min(line[i][1], line[i][0] + line[i][2])
        else : 
            line[i][0] += line[i-1][0]
            line[i][1] += line[i-1][1]
            if(i != n-1):
                line[i][0] = min(line[i][0], line[i][1] + line[i][3])
                line[i][1] = min(line[i][1], line[i][0] + line[i][2])
print(min(line[n-1][0], line[n-1][1]))