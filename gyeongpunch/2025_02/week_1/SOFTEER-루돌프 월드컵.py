from itertools import product
import sys

def get_prob(f1, f2):
    win = 4*f1 / (5*f1+5*f2)
    lose = 4*f2 / (5*f1+5*f2)
    draw = 0.2
    return win, lose, draw

def simulation():
    probs = dict()
    matches = []
    for i in range(3):
        for j in range(i+1, 4):
            probs[(i, j)] = get_prob(arr[i], arr[j])
            matches.append((i, j))

    outcomes = list(product([0, 1, 2], repeat=6))
    total_prob = 0

    for outcome in outcomes:
        score = [0, 0, 0, 0]
        prob = 1
        for k, result in enumerate(outcome):
            i, j = matches[k]

            if result==0:
                prob *= probs[(i, j)][0]
                score[i] += 3
                
            elif result == 1:
                prob *= probs[(i, j)][1]
                score[j] += 3
                
            elif result == 2:
                prob *= probs[(i, j)][2]
                score[i] += 1
                score[j] += 1

        sorted_score = sorted([(score[i], i) for i in range(4)], key=lambda x : (-x[0], x[1]))
        top_2 = [idx for _, idx in sorted_score][:2]

        if 0 in top_2:
            total_prob += prob
    return total_prob * 100

arr = list(map(int, input().split()))

result = simulation()

print(f"{result:.3f}")