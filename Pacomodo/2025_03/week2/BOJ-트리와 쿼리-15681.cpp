// 15681번 트리와 쿼리
// 트리 DP
/*
접근 방법: 
DP[i] = i번째 노드가 서브트리의 루트라고 할 때, 그 서브트리에 속한 정점의 수
라고 정의합시다. 

그러면 우리는 결국, DP[root]의 값을 구하고 싶은 것입니다.
DP[root] = sum(DP[child node of root])가 됩니다.

이를 어떻게 구하냐? Topdown DP로 구합니다. 즉, 재귀적으로 구하면 됩니다.
피보나치 수열처럼 구하면 충분합니다.

일반적으로 트리 DP는 이렇게 트리를 "서브트리"로 나누어서, 위와 같이 DP테이블을 세웁니다. 
그리고 선형적인 구조가 아니기 때문에, BottomUp DP로 구하기가 힙듭니다.
탐색 순서가 입력에 따라 다르기 때문이죠.
따라서 일반적으로는 Topdown DP로 DP테이블을 채웁니다.
*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int topDown(const vector<vector<int>>& G, vector<int>& DP, vector<int>& vis, int node){
    if (DP[node] != -1){ // DP값이 존재한다면 DP값을 반환하도록 합시다.
        return DP[node];
    }
    // 그렇지 않다면 하위 노드에 대해서 DP값을 찾아서 더해줍시다.
    vis[node] = 1; // 방문해줍시다.
    DP[node] = 1; // 일단 자기 자신이 있습니다.
    for (int nearNode: G[node]){
        if (vis[nearNode] == 0){ // 방문하지 않았다면, 즉, 하위 노드라면,
            DP[node] += topDown(G, DP, vis, nearNode); // 그 값을 더해줍시다.
        }
    }
    return DP[node];
}

int main(void){
    fastio;
    size_t N, R, Q; cin >> N >> R >> Q; // 트리의 정점의 수, 루트의 번호, 쿼리의 수.
    vector<vector<int>> graph(N+1);
    vector<int> vis(N+1, 0);
    int u, v;
    for (size_t i = 0; i < N-1; ++i){
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // 이제 Topdown DP를 통해 DP테이블을 채워봅시다.
    vector<int> DP(N+1, -1);
    topDown(graph, DP, vis, R);
    int queryNode;
    while (Q--){
        cin >> queryNode;
        cout << DP[queryNode] << endl;
    }
    return 0;
}