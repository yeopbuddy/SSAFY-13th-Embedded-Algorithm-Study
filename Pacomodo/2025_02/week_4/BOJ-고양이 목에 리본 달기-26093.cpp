// 26093번 고양이 목에 리본 달기
// DP
/*
문제 요약:
N마리의 고양이에게 리본을 달자. 리본은 K종류의 리본이 있다.
각 고양이마다 리본 종류의 선호도가 다르다. 고양이를 번호 순으로 세우고 리본을 단다.
자신과 이웃한 고양이와 같은 종류의 리본을 다는 것이 안됨.

접근 방법:
점화식을 다음과 같이 세우자.
DP[i][j] = 지금까지 i번째 고양이를 보았고, 그 고양이에게 j번 리본을 달았을 때 리본에 대한 만족도의 총 합.
DP[i][j] = max(DP[i-1][k]) k=0~K-1 except j + A[i][j]
고양이의 수가 최대 100마리고, 리본 종류의 수가 최대 10000가지이므로, O(NK)의 시간복잡도로 통과해야한다.
max(DP[i-1][k])except j의 값을 어떻게 빠르게 구할 수 있을까?
우리는 최댓값과 그때의 인덱스, 두번째로 큰 값과 그때의 인덱스만 들고 있으면 충분하다.
이 값을 계속 저장해주자.
*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    // 고양이의 수, 리본의 종류
    int N, K; cin >> N >> K;
    vector<vector<int>> a(N, vector<int>(K));
    vector<vector<int>> DP(N, vector<int>(K, 0));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < K; j++){
            cin >> a[i][j];
        }
    }
    // 초깃값 설정
    for (int j = 0; j < K; j++){
        DP[0][j] = a[0][j];
    }
    // DP 점화식
    for (int i = 1; i < N; i++){
        // 최댓값과 그때의 인덱스
        int first_max_val = 0, first_max_idx = 0;
        for (int j = 0; j < K; j++){
            if (DP[i-1][j] > first_max_val){
                first_max_val = DP[i-1][j];
                first_max_idx = j;
            }
        }
        // 두번째로 큰 값과 그때의 인덱스
        int second_max_val = 0, second_max_idx = 0;
        for (int j = 0; j < K; j++){
            if (DP[i-1][j] > second_max_val && j != first_max_idx){
                second_max_val = DP[i-1][j];
                second_max_idx = j;
            }
        }
        // DP[i][j] 구하기
        for (int j = 0; j < K; j++){
            if (j == first_max_idx) DP[i][j] = a[i][j] + second_max_val;
            else DP[i][j] = a[i][j] + first_max_val;
        }
    }
    int ans = 0;
    for (int j = 0; j < K; j++){
        ans = max(ans, DP[N-1][j]);
    }
    cout << ans;
    return 0;
}