from collections import Counter
import sys
input = sys.stdin.readline
N, M = map(int, input().split())
cpti_list = [input().strip() for _ in range(N)]
count = 0
cpti_count = Counter(int(cpti, 2) for cpti in cpti_list)
cpti_keys = list(cpti_count.keys()) 

for i, cpti in enumerate(cpti_keys):
    count += (cpti_count[cpti] * (cpti_count[cpti] - 1)) // 2
    
    for j in range(M):
        flipped_1 = cpti ^ (1 << j)
        if flipped_1 in cpti_count and flipped_1 > cpti: 
            count += cpti_count[cpti] * cpti_count[flipped_1]

        for k in range(j + 1, M):
            flipped_2 = flipped_1 ^ (1 << k)
            if flipped_2 in cpti_count and flipped_2 > cpti:
                count += cpti_count[cpti] * cpti_count[flipped_2]

print(count)