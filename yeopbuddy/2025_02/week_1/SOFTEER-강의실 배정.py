import sys
input = sys.stdin.readline
n = int(input())
lecture = [list(map(int, input().split())) for _ in range(n)]
lecture.sort(key=lambda x : x[1])
possible = 1
endtime = lecture[0][1]
for i in range(1, n):
    if endtime <= lecture[i][0]:
        endtime = lecture[i][1]
        possible += 1
print(possible)