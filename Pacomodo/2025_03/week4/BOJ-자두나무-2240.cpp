#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(){
    fastio;
    int T, W; cin >> T >> W;
    vector<vector<int>> jadoo(T, vector<int>(2, 0));
    for (int i = 0; i < T; i++){
        int tree;
        cin >> tree;
        jadoo[i][tree - 1] = 1;
    }
    vector<vector<vector<int>>> DP(T, vector<vector<int>>(2, vector<int>(W+1, 0)));
    DP[0][0][0] = jadoo[0][0];
    if(W > 0)
        DP[0][1][1] = jadoo[0][1];
    for (int i = 1; i < T; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k <= W; k++){
                if (k >= 1){
                    DP[i][j][k] = max(DP[i-1][j][k], DP[i-1][1-j][k-1]) + jadoo[i][j];
                } else { 
                    if (j == 0) DP[i][j][k] = DP[i-1][j][k] + jadoo[i][j];
                    else DP[i][j][k] = DP[i-1][j][k]; 
                }
            }
        }
    }
    int answer = 0;
    for (int k = 0; k <= W; k++){
        answer = max(answer, DP[T-1][0][k]);
    }
    for (int k = 1; k <= W; k++){
        answer = max(answer, DP[T-1][1][k]);
    }
    cout << answer;
    return 0;
}
