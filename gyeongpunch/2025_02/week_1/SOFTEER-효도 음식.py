def max_satisfaction(n, arr):
    left_max = [0] * n
    current_sum = arr[0]
    left_max[0] = current_sum
    for i in range(1, n):
        current_sum = max(arr[i], current_sum + arr[i])
        left_max[i] = max(left_max[i - 1], current_sum)

    right_max = [0] * n
    current_sum = arr[-1]
    right_max[-1] = current_sum
    for i in range(n - 2, -1, -1):
        current_sum = max(arr[i], current_sum + arr[i])
        right_max[i] = max(right_max[i + 1], current_sum)

    max_satisfaction = float('-inf')
    for i in range(n - 2):
        max_satisfaction = max(max_satisfaction, left_max[i] + right_max[i + 2])

    return max_satisfaction

n = int(input())
arr = list(map(int, input().split()))

print(max_satisfaction(n, arr))
