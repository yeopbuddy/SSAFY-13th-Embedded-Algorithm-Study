#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;

// dp table 정의하는 법은 구글링했습니다.ㅎㅎ
// dp[i][j]: i번째부터 j번째까지 합치는 최소 비용
// i부터 j까지 합치는 방법은 (i) / (i+1, ... , j)
//                     (i, i+1) / (i+2, ... , j)
//                      ........ 이 있습니다.
//                      이들 중 최소값으로 업데이트합니다.
// 파일1과 파일2을 합칠 때는 파일1, 파일2에 포함된 모든 파일의 크기가 더해집니다.
// 누적합을 사용해서 i부터 j까지의 합을 빠르게 구할 수 있습니다.
// i번째부터 i번째까지 자기자신이므로 합치는 최소 비용은 항상 0입니다.

const int MAX = 500;

int N;
int arr[MAX];
int sm[MAX + 1] = {0};
int dp[MAX+1][MAX+1] = {0};

int simulation(){
    for(int y=2; y<=N; y++){
        for(int x=y-1; x>0; x--){
            dp[x][y] = 1e9;
            for(int k=0; k<y-x; k++){
                dp[x][y] = min(dp[x][y], dp[x][x+k] + dp[x+k+1][y] + sm[y] - sm[x-1]);
            }
        }
    }
    return dp[1][N];
}

int main(void){
    fastio;

    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for(int t=1; t<=T; t++){

        cin >> N;
        for(int i=0; i<N; i++){
            cin >> arr[i];
            sm[i+1] = sm[i] + arr[i];
        }

        int result = simulation();
        cout << result << '\n';
    }
    return 0;
}