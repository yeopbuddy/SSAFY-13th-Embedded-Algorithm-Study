// 소프티어 징검다리
// DP
/*
접근 방법:
DP[i] = i번 돌을 무조건 밟을 때 밟을 수 있는 돌의 최대 개수
DP[i] = max(DP[j] where A[j] < A[i] for j < i)+1
이러면 O(N^2)에 해결 가능
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef long long ll;

int main(void){
    fastio;
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    vector<int> DP(N, 1);
    DP[0] = 1;
    for (int i = 1; i < N; i++){
        for (int j = 0; j < i; j++){
            if (A[j] < A[i]) DP[i] = max(DP[j]+1, DP[i]);
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++){
        ans = max(DP[i], ans);
    }
    cout << ans;
    return 0;
}