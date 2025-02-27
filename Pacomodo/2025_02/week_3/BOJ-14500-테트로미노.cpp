// 14500번 테트로미노
// DFS + 약간의 구현
/*
접근 방법:
T자를 제외한 나머지 모양은 DFS돌리면 됨.
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

int N, M;
int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};

void DFS(const vector<vector<int>>& MAP, vector<vector<bool>>& vis, pair<int, int> now, int depth, int S, int& MAX){
    if (depth == 0){
        MAX = max(S, MAX);
        return;
    }
    for (int i = 0; i < 4; i++){
        int nr = now.first+dr[i], nc = now.second+dc[i];
        if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
        if (vis[nr][nc]) continue;
        vis[nr][nc] = 1;
        DFS(MAP, vis, {nr, nc}, depth-1, S+MAP[nr][nc], MAX);
        vis[nr][nc] = 0;
    }
    return;
}

void I_LIKE_TT(const vector<vector<int>>& MAP, pair<int, int> now, int& MAX){
    for (int i = 0; i < 4; i++){
        int A = MAP[now.first][now.second];
        for (int j = 0; j < 3; j++){
            int nr = now.first+dr[(i+j)%4], nc = now.second+dc[(i+j)%4];
            if (0 <= nr && nr < N && 0 <= nc && nc < M){
                A += MAP[nr][nc];
            }
        }
        MAX = max(MAX, A);
    }
}

int main(void){
    fastio;
    cin >> N >> M;
    vector<vector<int>> MAP(N, vector<int>(M));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> MAP[i][j];
        }
    }
    vector<vector<bool>> vis(N, vector<bool>(M, 0));
    int MAX = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            vis[i][j] = 1;
            DFS(MAP, vis, {i, j}, 3, MAP[i][j], MAX);
            I_LIKE_TT(MAP, {i, j}, MAX);
            vis[i][j] = 0;
        }
    }
    cout << MAX;
    return 0;
}