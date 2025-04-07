#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main() {
    fastio;    
    int N, M, K;
    cin >> N >> M >> K;
    vector<string> board(N);
    for (int i = 0; i < N; i++) {
        cin >> board[i];
    }

    vector<vector<int>> DP(N, vector<int>(M, -1));
    DP[N-1][M-1] = 0;
    
    for (int i = N - 1; i >= 0; i--) {
        for (int j = M - 1; j >= 0; j--) {
            if (board[i][j] == '#') continue;
            if (i == N - 1 && j == M - 1) continue;
            
            bool flag = true;
            if (i + 1 < N && board[i+1][j] == '.' && DP[i+1][j] == 0)
                flag = false;
            if (flag && j + 1 < M && board[i][j+1] == '.' && DP[i][j+1] == 0)
                flag = false;
            if (flag) {
                for (int k = 1; k <= K; k++) {
                    if (i + k < N && j + k < M && board[i+k][j+k] == '.' && DP[i+k][j+k] == 0) {
                        flag = false;
                        break;
                    }
                }
            }
            DP[i][j] = flag ? 0 : 1;
        }
    }
    
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (DP[x][y] == 1)
            cout << "First" << "\n";
        else
            cout << "Second" << "\n";
    }
    return 0;
}
