// 2450번 모양 정돈
// 그리디, 정렬
/*
접근 방법: 
N은 최대 10만
예제 분석:
1 1 1 2 2 3 3 3
1 1 1 3 3 3 2 2 
2 2 1 1 1 3 3 3
2 2 3 3 3 1 1 1
3 3 3 1 1 1 2 2
3 3 3 2 2 1 1 1
6가지 나열의 경우의 수가 있다.
각 경우의 수, 예를 들어 1 1 1 2 2 3 3 3이라면,
1 3 3 2 1 1 3 2
1 1 1 2 2 3 3 3
DP[i][j] = i가 j위치에 있음.
ex)DP[3][1] = 3이 1위치에 있음
DP[3][1]과 DP[1][3]은 한번의 교환으로 가능함.
1 3 3 2 1 1 3 2
1 1 1 2 2 3 3 3
DP[3][1] = 2 -> 1
DP[1][2] = 1
DP[1][3] = 1 -> 0
DP[2][3] = 1
이후 남은 것들을 다 더하고 2를 곱하고 3으로 나누면 된다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int solve(const vector<int>& CASE, const vector<int>& A, vector<int> cnt){
    int N = A.size();
    vector<int> IDEAL(N);
    int idx = 0;
    for (int i = 0; i < N; i++){
        if (cnt[CASE[idx]] != 0){
            IDEAL[i] = CASE[idx];
            cnt[CASE[idx]]--;
        } else {
            idx++;
            IDEAL[i] = CASE[idx];
            cnt[CASE[idx]]--;
        }
    }
    vector<vector<int>> DP(4, vector<int>(4, 0));
    for (int idx = 0; idx < N; idx++){
        int i = A[idx], j = IDEAL[idx];
        DP[i][j]++; 
    }
    int ret = 0, remain = 0;
    for (int i = 1; i <= 2; i++){
        for (int j = i+1; j <= 3; j++){
            ret += min(DP[i][j], DP[j][i]);
            remain += max(DP[i][j], DP[j][i]) - min(DP[i][j], DP[j][i]);
        }
    }
    ret += 2*remain/3;
    return ret;
}

int main(void){
    fastio;
    int N; cin >> N;
    vector<int> A(N);
    vector<int> cnt(4, 0);
    for (int i = 0; i < N; i++){
        cin >> A[i];
        if (A[i] == 1){
            cnt[1]++;
        } else if (A[i] == 2){
            cnt[2]++;
        } else {
            cnt[3]++;
        }
    }
    vector<vector<int>> CASE_WORK = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
    int ans = 1'000'000;
    for (auto CASE: CASE_WORK){
        ans = min(ans, solve(CASE, A, cnt));
    }
    cout << ans;
    return 0;
}