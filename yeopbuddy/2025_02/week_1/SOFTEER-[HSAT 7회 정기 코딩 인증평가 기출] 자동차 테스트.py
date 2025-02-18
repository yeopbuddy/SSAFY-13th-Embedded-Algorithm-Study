import sys
input = sys.stdin.readline
n, q = map(int, input().split())
_list = list(map(int, input().split()))
_list.sort()
dd = {_list[i] : i for i in range(n)}
for _ in range(q):
    m = int(input())
    try:
        if(dd[m] == 0 or dd[m] == n - 1):
            print("0")
        else:
            print(dd[m] * (n - 1 - dd[m]))
    except:
        print("0")