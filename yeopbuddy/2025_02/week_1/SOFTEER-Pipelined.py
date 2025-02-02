import sys
n = int(input())
_list = map(int, input().split())
print(max(_list) + n - 1)