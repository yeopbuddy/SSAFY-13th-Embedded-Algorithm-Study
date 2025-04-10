// 30893번 트리 게임
// 게임 이론, 그래프 탐색, 차수열
/*
접근 방법: 
선공의 움직이는 방향은 항상 도착지점으로 향하는 방향이다.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    int N, S, E; cin >> N >> S >> E;
    vector<vector<int>> G(N+1);
    vector<int> degree(N+1, 0);
    int u, v;
    for (int i = 0; i < N-1; i++){
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    vector<int> visited(N+1, 0);
    vector<int> parent(N+1, -1);
    queue<int> Q;
    Q.push(S);
    visited[S] = 1;
    vector<int> route;
    while (!Q.empty()){
        int now = Q.front();
        if (now == E){
            route.push_back(now);
            while (now != S){
                now = parent[now];
                route.push_back(now);
            }
            break;
        }
        Q.pop();
        for (auto near: G[now]){
            if (!visited[near]){
                visited[near] = 1;
                parent[near] = now;
                Q.push(near);
            }
        }
    }
    bool flag = false; // false면 선공차례, true면 후공차례.
    bool win_lose = true; // true면 선공이 이김.
    while (route.size() > 1){
        int now = route.back();
        route.pop_back();
        if (flag && degree[now] != 2){
            win_lose = false;
            break;
        }
        flag = !flag;
    }
    cout << (win_lose ? "First" : "Second") << endl;
    return 0;
}