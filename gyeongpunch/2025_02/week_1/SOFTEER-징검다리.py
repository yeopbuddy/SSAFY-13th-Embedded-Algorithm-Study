import bisect
import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))

lst = []
length = 0
for num in arr:
    pos = bisect.bisect_left(lst, num)

    if pos == length:
        lst.append(num)
        length += 1
    else:
        lst[pos] = num

print(length)