// 12181번 Googlander (Large)
// DP
/*
접근 방법:

*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
typedef long long ll;

int main(void){
    vector<vector<ll>> DP(25, vector<ll>(25, 0));
    for (int i = 0; i < 25; i++){
        DP[0][i] = 1;
        DP[i][0] = 1;
    }
    for (int i = 1; i < 25; i++){
        for (int j = 1; j < 25; j++){
            DP[i][j] = DP[i-1][j] + DP[i][j-1];
        }
    }
    int T, r, c; cin >> T;
    for (int i = 1; i <= T; i++){
        cin >> r >> c;
        cout << "Case #" << i << ": " << DP[r-1][c-1] << endl;
    }
    return 0;
}