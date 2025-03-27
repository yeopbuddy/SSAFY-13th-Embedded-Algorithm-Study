#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int N;
vector<int> DP;
vector<bool> visited;
vector<vector<int>> tree;

void dfs(int i) {
    visited[i] = true;
    vector<int> li;
    for (int child : tree[i]) {
        if (!visited[child]) {
            dfs(child);
            li.push_back(DP[child]);
        }
    }
    // 내림차순 정렬
    sort(li.begin(), li.end(), greater<int>());
    // li의 각 원소에 (index+1) 을 더함
    for (int j = 0; j < li.size(); j++) {
        li[j] += j + 1;
    }
    if (li.empty())
        DP[i] = 0;
    else
        DP[i] = *max_element(li.begin(), li.end());
}

int main(){
    fastio;
    cin >> N;
    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }
    
    // 트리 구성 (0번 노드를 루트로 가정)
    tree.resize(N);
    for (int i = 1; i < N; i++) {
        int parent = T[i];
        tree[i].push_back(parent);
        tree[parent].push_back(i);
    }
    
    DP.resize(N);
    visited.assign(N, false);
    
    dfs(0);
    
    cout << DP[0] << endl;
    return 0;
}
