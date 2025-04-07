#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// 공부 효율(시간 당 올릴 수 있는 점수)이 좋은 순으로 정렬하는 우선순위 큐를 사용한다.
struct Obj {
    int score_current;
    int score_increase;
    Obj(int s1, int s2) {
        score_current = s1;
        score_increase = s2;
    }
    bool operator<(const Obj& ob)const { // ex. 효율이 4, 점수가 98인 경우 100점을 넘을 수 없으므로 이때 효율은 2이다.
        int o1 = 100 - score_current; // 따라서 효율을 min(100 - 현재 점수, 점수 증가율) 로 잡아 우선순위를 매기고, 큐에 넣고 빼고를 반복한다.
        int o2 = 100 - ob.score_current;
        if (o1 > score_increase) {
            o1 = score_increase;
        }
        if (o2 > ob.score_increase) {
            o2 = ob.score_increase;
        }
        return o1 < o2;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    n *= 24;

    vector<vector<int>> ScoreBoard(2, vector<int>(m));
    for (int i = 0; i < m; i++) {
        cin >> ScoreBoard[0][i];
    }
    for (int i = 0; i < m; i++) {
        cin >> ScoreBoard[1][i];
    }

    priority_queue<Obj> pq;
    for (int i = 0; i < m; i++) {
        pq.push(Obj(ScoreBoard[0][i], ScoreBoard[1][i]));
    }

    while (n != 0) {
        int poped_score, poped_inc, new_score;
        poped_score = pq.top().score_current;
        poped_inc = pq.top().score_increase;
        pq.pop();
        if (100 - poped_score >= poped_inc) {
            if (((100 - poped_score) / poped_inc) > n) {
                new_score = poped_score + (poped_inc * n);
                n = 0;
            }
            else {
                new_score = poped_score + ((100 - poped_score) / poped_inc) * poped_inc;
                n -= ((100 - poped_score) / poped_inc);
            }
        }
        else {
            new_score = 100;
            n -= 1;
        }
        pq.push(Obj(new_score, poped_inc));
    }
    int total = 0;
    while (!pq.empty()) {
        int poped_score, poped_inc;
        poped_score = pq.top().score_current;
        total += poped_score;
        pq.pop();
    }
    cout << total;
    return 0;
}