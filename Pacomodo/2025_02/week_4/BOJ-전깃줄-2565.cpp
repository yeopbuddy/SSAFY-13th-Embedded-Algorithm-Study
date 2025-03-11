// 2565번 전깃줄
// DP
/*
접근 방법:
LIS
DP[i] = i번째 원소를 볼 때 가장 긴 증가하는 부분수열
DP[i] = max(DP[j] where A[j] < A[i]) + 1
*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    int N; cin >> N;
    int B[501] = {0,};
    int a, b;
    for (int i = 0; i < N; i++){
        cin >> a >> b;
        B[b] = a;
    }
    vector<int> A;
    for (int i = 0; i < 501; i++){
        if (B[i]){
            A.push_back(B[i]);
        }
    }
    N = A.size();
    vector<int> DP(N, 0);
    DP[0] = 1;
    for (int i = 1; i < N; i++){
        int M = 0;
        for (int j = 0; j < i; j++){
            if (A[j] < A[i] && M < DP[j]){
                M = DP[j];
            }
        }
        DP[i] = M+1;
    }
    int M = 0;
    for (int i = 0; i < N; i++){
        M = max(DP[i], M);
    }
    cout << N - M;
}