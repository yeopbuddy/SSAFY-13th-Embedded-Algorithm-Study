// 2146번 다리 만들기
// BFS
/*
접근 방법:

*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
typedef long long ll;

int BFS1(vector<vector<int>>& MAP, pair<int, int> start){
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    int N = MAP.size();
    vector<vector<int>> vis(N, vector<int>(N, 0));
    queue<pair<int, int>> Q1, Q2;
    Q1.push(start);
    Q2.push(start);
    vis[start.first][start.second] = 1;
    MAP[start.first][start.second] = 0;
    while (!Q1.empty()){
        pair<int, int> pos = Q1.front();
        Q1.pop();
        for (int i = 0; i < 4; i++){
            int nr = pos.first+dr[i], nc = pos.second+dc[i];
            if (0 > nr || N <= nr || 0 > nc || N <= nc) continue;
            if (vis[nr][nc]) continue;
            if (MAP[nr][nc] == 0) continue;
            vis[nr][nc] = 1;
            MAP[nr][nc] = 0;
            Q1.push({nr, nc});
            Q2.push({nr, nc});
        }
    }
    while (!Q2.empty()){
        pair<int, int> pos = Q2.front();
        if (MAP[pos.first][pos.second] != 0){
            return vis[pos.first][pos.second] - 2;
        }
        Q2.pop();
        for (int i = 0; i < 4; i++){
            int nr = pos.first+dr[i], nc = pos.second+dc[i];
            if (0 > nr || N <= nr || 0 > nc || N <= nc) continue;
            if (vis[nr][nc] > 0) continue;
            vis[nr][nc] = vis[pos.first][pos.second] + 1;
            Q2.push({nr, nc});
        }
    }
    return 100000000;
}



int main(void){
    fastio;
    int N, M; cin >> N;
    vector<vector<int>> MAP(N, vector<int>(N));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> MAP[i][j];
        }
    }
    int ans = 1000000;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (MAP[i][j] != 0){
                ans = min(ans, BFS1(MAP, {i, j}));
            }
        }
    }
    cout << ans;
    return 0;
}