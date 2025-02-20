// 11066번 파일 합치기
// 분할정복, DP, 누적합
/*
접근 방법:
어쨌든간에 맨 마지막에 두개의 파일을 합쳐야 됨
(왼쪽) + (오른쪽)
15개의 예시라면
(1개) + (14개일때 최소)
(2개일때의 최소) + (13개일때의 최소)...
(15개일때의 최소) + (1개일때의 최소)
중 최솟값이 답이 된다.
DP[i][j] = i번부터 j번까지 파일을 합칠 때 드는 최소 비용
DP[i][j] = min(accum[j+1] - accum[i] + DP[i][s] + DP[s+1][j]) where s = i to j-1
DP[i][i] = A[i];
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
typedef long long ll;

int top_down(const vector<ll>& accum, vector<vector<ll>>& DP, int l, int r){
    if (DP[l][r] != 1'000'000'000'000) return DP[l][r];
    ll left, right, ans = 1'000'000'000'000;
    for (int s = l; s < r; s++){
        left = top_down(accum, DP, l, s);
        right = top_down(accum, DP, s+1, r);
        ans = min(accum[r+1] - accum[l] + left + right, ans);
    }
    DP[l][r] = ans;
    return DP[l][r];
}

void solve(void){
    int N; cin >> N;
    vector<vector<ll>> DP(N, vector<ll>(N, 1'000'000'000'000));
    vector<ll> A(N);
    vector<ll> accum(N+1, 0);
    for (int i = 0; i < N; i++){
        cin >> A[i];
        DP[i][i] = 0;
        accum[i+1] = accum[i] + A[i];
    }
    for (int i = 0; i < N-1; i++){
        DP[i][i+1] = A[i]+A[i+1];
    }
    cout << top_down(accum, DP, 0, N-1) << endl;
    return;
}

int main(void){
    int T; cin >> T;
    while (T--){
        solve();
    }
    return 0;
}