from collections import deque
import sys

input = sys.stdin.readline

def simulation():
    curr_queue = deque([(arr[i], i+1) for i in range(N)])
    next_queue = deque([])

    while len(curr_queue) > 1:
        while curr_queue:
            curr_size, curr_idx = curr_queue.popleft()
            tmp = curr_size

            if next_queue and next_queue[-1][0] <= curr_size:
                p = next_queue.pop()
                tmp += p[0]

            if curr_queue and curr_queue[0][0] <= curr_size:
                n = curr_queue.popleft()
                tmp += n[0]

            next_queue.append((tmp, curr_idx))

        curr_queue = next_queue
        next_queue = deque()

    return curr_queue[0][0], curr_queue[0][1]

N = int(input())
arr = list(map(int, input().split()))

total_size, init_idx = simulation()

print(total_size)
print(init_idx)
