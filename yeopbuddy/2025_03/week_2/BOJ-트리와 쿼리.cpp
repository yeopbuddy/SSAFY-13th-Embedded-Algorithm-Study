#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> TREE;
vector<int> DP;
bool visited[100001];

int DFS(int node) {
    visited[node] = true;
    DP[node] = 1;
    for (int child : TREE[node]) {
        if (!visited[child]) {
            DP[node] += DFS(child);
        }
    }
    return DP[node];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, r, q; 
    cin >> n >> r >> q;
    TREE.resize(n + 1);
    DP.resize(n + 1, 0);

    for (int i = 1; i < n; i++) {
        int u, v; 
        cin >> u >> v;
        TREE[u].push_back(v);
        TREE[v].push_back(u);
    }

    DFS(r);

    for (int i = 0; i < q; i++) {
        int query;
        cin >> query;
        cout << DP[query] << "\n";
    }

    return 0;
}