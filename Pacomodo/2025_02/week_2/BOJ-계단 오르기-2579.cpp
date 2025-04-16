// 2579번 계단 오르기
// DP
/*
접근 방법:
DP[i] = i번째 계단를 무조건 밟았을 때 얻을 수 있는 총 점수의 최댓값

연속한 세 계단을 밟아선 안된다
그 말은 내가 i번째 계단을 밟고, 그 이전 계단을 밟았다면, i-2번째 계단은 안밟았다는 소리다
그래서 2가지 경우가 나온다
1. 내가 i-1번째 계단을 밟고, i번째 계단을 밟은 경우
2. 내가 i-2번째 계단을 밟고 i번째 계단을 밟은 경우

둘 중 하나의 경우에서 최댓값이 나온다
1번의 경우 i-2번째 계단을 밟지 않았다는 것이 보장되므로, i-3번째 계단을 밟은것이다.
따라서 DP[i-3]의 값을 더해줘야 한다
따라서 다음과 같은 점화식이 나온다
DP[i] = max(DP[i-3] + A[i-1], DP[i-2]) + A[i]
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    int N; cin >> N;
    vector<int> DP(N, 0);
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    DP[0] = A[0];
    if (N == 1){
        cout << DP[0] << endl;
        return 0;
    }
    DP[1] = A[0]+A[1];
    if (N == 2){
        cout << DP[1] << endl;
        return 0;
    }
    DP[2] = A[2]+max(A[0], A[1]);
    for (int i = 3; i < N; i++){
        DP[i] = max(DP[i-3] + A[i-1], DP[i-2]) + A[i];
    }
    cout << DP[N-1] << endl;
    return 0;
}