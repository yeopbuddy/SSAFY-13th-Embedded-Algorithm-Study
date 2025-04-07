#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);
#define MAX_N 100001

/*
선공: 무조건 목표 정점으로 도착해야함
후공: 목표 정점으로 못 가게 해야함

선공차례일 때는 아무데나 갈 수 있습니다.
근데 후공차례일 때는 branch가 2개 이상이면 다른 곳으로 빠져서 목표 정점으로 못 가게 할 수 있습니다.
트리 구조라서 가능
둘 다 최선의 전략을 이미 알고(Algorithm)있으므로, 선공이 목표 정점에 도착하는 시나리오가 하나라도 있으면 선공을 선택하고 후공이 어느 상황이든 절대 도착할 수 없게 만들 수 있으면 후공을 선택합시다.

1. 늘 먹던대로 tree를 저장합니다.
2. bfs를 돌립니다. Node.who: 선공(0)인지 후공(1)인지
3. tree[now.n]에서 아직 방문하지 않은 노드들을 nxt에 담습니다.
4. now.who == 1 (후공일 때는) nxt의 사이즈가 1보다 크면 다른 길로 빠지게 해서 목표 정점에 도착할 수 없게 할 수 있습니다.
5. now.who == 0 (선공일 때는) 아무데나 다 갈 수 있으니까, 방문 가능한 모든 노드를 q에 담아봅시다.
*/

struct Node{
    int n, who;
};

int N, S, E;
vector<int> tree[MAX_N];
int visited[MAX_N];

bool bfs() {
    queue<Node> q;
    q.push({S, 0});
    visited[S] = 1;
    
    while (!q.empty()) {
        Node now = q.front(); q.pop();
        
        if (now.n == E) return true;
        
        vector<int> next;
        for (int nxt : tree[now.n]) {
            if (visited[nxt] == 0)
                next.push_back(nxt);
        }
        int cnt = next.size();
        
        if (now.who == 1) {
            if (cnt > 1) continue;
            if (cnt == 1) {
                int nxt = next[0];
                visited[nxt] = 1;
                q.push({nxt, 0});
            }
        }
        else {
            for (int nxt : next) {
                visited[nxt] = 1;
                q.push({nxt, 1});
            }
        }
    }
    return false;
}

int main(void){
    fastio;

    // freopen("input.txt", "r", stdin);

    cin >> N >> S >> E;
    int a, b;
    for(int i = 0; i < N - 1; i++){
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    if(bfs())
        cout << "First";
    else
        cout << "Second";
    
    return 0;
}
