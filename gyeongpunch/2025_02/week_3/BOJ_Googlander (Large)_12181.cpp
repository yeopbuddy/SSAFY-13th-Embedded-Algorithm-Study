#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// dfs로 풀었습니다. row 수가 한 칸일 때 중복 계산되지 않도록 dfs(N-1, 0, 0);로 시작합니다.
// flag를 이용해서 이동할 수 없을 때 result++하여 카운트합니다.

// 아니 이거 완전탐색이 터져버리잖아~?
// 이게 그리다보니까 DP이긴한데 명확하게 설명은 안 되네요.
// 저 점화식이 왜 되는 거지

// 아하 알았어요. 점화식이 정확히는 저렇게 되는 거네요.
// memset도 할 필요없이 바로 덮어쓰면 될 것 같아요.


int N, M, result;
long long visited[25][25] = {0};

void pprint(){
    cout << "============================\n";
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                cout << visited[i][j] << ' ';
            }
            cout << '\n';
        }
    cout << "============================\n";
}


int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;

    for(int t=1; t<=T; t++){
        cin >> N >> M;
        if(N==1 || M == 1){
            cout << "Case #" << t << ": " << 1 << '\n';
            continue;
        }
        
        for(int i=0; i<N; i++){
            visited[i][0] = 1;
        }
        for(int i=0; i<M; i++){
            visited[0][i] = 1;
        }

        for(int i=1; i<N; i++){
            for(int j=M-1; j>0; j--){
                visited[i][j] = (visited[i-1][j] + visited[i][(j + 1) % M]) * 1LL;
            }
        }
        
        cout << "Case #" << t << ": " << visited[N-1][1] << '\n';
    }
    return 0;
}