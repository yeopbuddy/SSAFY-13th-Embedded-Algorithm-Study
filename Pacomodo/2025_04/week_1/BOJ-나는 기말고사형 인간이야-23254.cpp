// 23254번 나는 기말고사형 인간이야
// 그리디, 우선순위 큐
/*
접근 방법:
올리는 수, 올릴 수 있는 점수로 쌍을 이뤄 우선 순위 큐에 넣는다.
(올릴 수 있는 점수) / (올리는 수) 만큼 시간을 소모하고, 다시 우큐에 넣는다.
만약 시간이 부족하다면, 그냥 (올리는 수) * (남은 시간)만큼 점수가 올라가는 것이다.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

struct score{
    int step, remain;
    bool operator<(const score& other) const {
        if (step == other.step) return remain < other.remain;
        return step < other.step;
    }
};

int main(void){
    fastio;
    int N, M; cin >> N >> M;
    int ans = 0;
    vector<int> A(M), B(M);
    for (int i = 0; i < M; i++){
        cin >> A[i];
        ans += A[i];
    }
    for (int i = 0; i < M; i++){
        cin >> B[i];
    }
    priority_queue<score> PQ;
    for (int i = 0; i < M; i++){
        PQ.push({B[i], 100-A[i]});
    }
    N = 24*N;
    while (!PQ.empty() && N > 0){
        int r = PQ.top().remain, s = PQ.top().step;
        if (s == 0) {
            PQ.pop();
            continue;
        }
        int cost = r / s;
        if (cost <= N){
            N -= cost;
            ans += cost * s;
            PQ.pop();
            PQ.push({r % s, r % s});
        } else {
            ans += N * s;
            N = 0;
        }
    }
    cout << ans << endl;
    return 0;
}