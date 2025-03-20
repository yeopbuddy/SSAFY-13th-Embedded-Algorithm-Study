// 2616번 소형기관차
// DP, 누적 합
/*
접근 방법:
나이브한 방법의 최악 케이스를 생각해봅시다.
객차가 50000개이고, 소형 기관차는 객차 1개만 나를 수 있다고 합시다.
그러면 50000개 중 3개를 뽑는 경우의 수 만큼의 시간 복잡도가 소요됩니다. 
이는 대략 20조 정도 되며, 1초라는 시간 제한에는 너무나도 오래걸리는 시간입니다.

따라서, DP접근 방식을 생각해봅시다.
DP테이블을 다음과 같이 정의합시다.

DP[j][i] =
현재 i번째 객차 칸을 보고 있고 소형 기관차가 이 칸을 운송할지 말지는 모르지만,
지금까지 소형 기관차 j대를 이용하였을 때 최대로 운송할 수 있는 손님 수.

이에 따르면, 우리가 찾고자 하는 값은 DP[3][N]이 됩니다.

현재 칸을 보고 있을 때, 최댓값이 나오는 경우는 3가지가 있습니다.
1. i-1번째 객차 칸을 보고 있었고, 이게 사실은 최대인 경우.
즉, 이전 상황과 동일하게 최대인 경우.
=> DP[j][i-1]

2. 현재 칸을 무조건 포함하도록 왼쪽으로 갔을 때 가장 
처음으로 만나는 기관차를 현재 칸으로 쭈욱 옮겨오는 경우.
이 경우 j-1대의 기관차는 그대로 두고 한대의 기관차를 쭉 옮기는 겁니다.
=> DP[j-1][i-K] + sum(연속된 객차 길이)

연속된 객차의 길이를 빠르게 구하기 위해 누적합을 사용합시다.
그러면 sum(연속된 객차의 길이) = accumA[i] - accumA[i-K]가 됩니다.
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    int N; cin >> N; // 객차의 수.
    vector<int> A(N);
    vector<int> accumA(N+1, 0);
    for (size_t i = 0; i < N; ++i){
        cin >> A[i];
        accumA[i+1] = A[i] + accumA[i];
    }
    int K; cin >> K; // 연속된 객차 길이
    vector<vector<int>> DP(4, vector<int>(N+1, 0));
    int a = 0, b = 0;
    for (int j = 1; j <= 3; ++j){
        for (int i = j*K; i < N+1; ++i){
            a = 0, b = 0;
            if (i-K >= 0) a = DP[j-1][i-K] + accumA[i] - accumA[i-K];
            if (i > 0) b = DP[j][i-1];
            DP[j][i] = max(a, b);
        }
    }
    cout << DP[3][N];
    return 0;
}