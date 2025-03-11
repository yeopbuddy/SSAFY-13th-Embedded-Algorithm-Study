// 2169번 로봇 조종하기
// DP
/*
접근 방법:
DP점화식을 다음과 같이 정의하자.
DP[i][j][0] = i번째 행과 j번째 열의 원소를 지나고, 로봇의 이전 움직임 방향이 아래 or 오른쪽 이었을 때의 최댓값
DP[i][j][1] = i번째 행과 j번째 열의 원소를 지나고, 로봇의 이전 움직임 방향이 아래 or 왼쪽 이었을 때의 최댓값

현재 위치(i, j)를 기준으로 보면 다음과 같다.
  DP[i-1][j][0], DP[i-1][j][1]
                ↓
DP[i][j-1][0] → □ ← DP[i][j-1][1]

DP[i][j][0] = (위 방향에서 온것들과 오른쪽방향에서 온 것 중 최댓값) + (현재 배열 값) 이므로
DP[i][j][0] = max(DP[i-1][j][0], DP[i-1][j][1], DP[i][j-1][0]) + A[i][j]

DP[i][j][1] = (위 방향에서 온것들과 왼쪽방향에서 온 것 중 최댓값) + (현재 배열 값) 이므로
DP[i][j][1] = max(DP[i-1][j][0], DP[i-1][j][1], DP[i][j+1][1]) + A[i][j]

인덱스를 넘어가서 참조하는 경우를 방지하기 위해
i == 0일때(맨 위일때),
DP[i][j][0]을 구하는데 j == 0일때,
DP[i][j][1]을 구하는데 j == 1일때의 경우를 잘 예외처리 해주었다.
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
typedef long long ll;
#define mINF -2'100'000'000

int top_down(const vector<vector<int>>& A, vector<vector<vector<int>>>& DP, int i, int j, int dir){
    if (i == 0){
        return DP[i][j][dir];
    }
    if (DP[i][j][dir] != mINF){
        return DP[i][j][dir];
    }
    int a = top_down(A, DP, i-1, j, dir);
    int b = top_down(A, DP, i-1, j, dir^1);
    int c;
    if (dir == 0){
        if (j == 0){
            DP[i][j][dir] = max(a, b) + A[i][j];
            return DP[i][j][dir];
        }
        c = top_down(A, DP, i, j-1, dir);
        DP[i][j][dir] = max(c, max(a, b)) + A[i][j];
    }
    else{
        if (j == DP[0].size()-1){
            DP[i][j][dir] = max(a, b) + A[i][j];
            return DP[i][j][dir];
        }
        c = top_down(A, DP, i, j+1, dir);
        DP[i][j][dir] = max(c, max(a, b)) + A[i][j];
    }
    return DP[i][j][dir];
}

int main(void){
    fastio;
    int N, M; cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> A[i][j];
        }
    }
    vector<vector<vector<int>>> DP(N, vector<vector<int>>(M, vector<int>(2, mINF)));
    DP[0][0][0] = A[0][0];
    for (int i = 1; i < M; i++){
        DP[0][i][0] = DP[0][i-1][0] + A[0][i];
    }
    cout << top_down(A, DP, N-1, M-1, 0);
}