# 20207번 달력
# 구현, 스위핑
'''
접근 방법:
스위핑으로 숫자가 시작하는 구간 ~ 끝나는 구간을 찾아줌
그 구간의 최댓값 찾음
'''
import sys
input = sys.stdin.readline

day = [0 for _ in range(365+1)]
N = int(input())
for _ in range(N):
    S, E = map(int, input().rstrip().split())
    for i in range(S, E+1):
        day[i] += 1

max_section = 0
section_length = 0
total = 0
for i in range(365+1):
    if day[i] == 0:
        total += section_length*max_section
        section_length = 0
        max_section = 0
    else:
        section_length += 1
        if day[i] > max_section:
            max_section = day[i]
total += section_length*max_section

print(total)