#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, s, e;
vector<vector<int>> GRAPH;
bool visit[100000] = {false};
vector<int> parent;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> s >> e;
    --s; --e;

    GRAPH.resize(n);
    parent.assign(n, -1);

    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; --u; --v;
        GRAPH[u].push_back(v);
        GRAPH[v].push_back(u);
    }

    queue<int> q;
    q.push(s);
    visit[s] = true;

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        if (cur == e) break;
        for (int next : GRAPH[cur]) {
            if (!visit[next]) {
                visit[next] = true;
                parent[next] = cur;
                q.push(next);
            }
        }
    }

    // 경로 역추적
    vector<int> path;
    int node = e;
    while (node != -1) {
        path.push_back(node);
        node = parent[node];
    }
    reverse(path.begin(), path.end());
    // for(int pt : path){
    //     cout << pt << " ";
    // }
    bool fstwin = true;
    for (int i = 1; i < path.size() - 1; i += 2) {
        if (GRAPH[path[i]].size() != 2) {
            fstwin = false;
            break;
        }
    }
    
    cout << (fstwin ? "First" : "Second");
}
