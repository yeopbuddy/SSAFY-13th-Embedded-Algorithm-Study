#include <iostream>
#include <vector>
#include <deque>
using namespace std;
bool visit[50001];
int level[50001];
int parent[50001];

int UP(int node){
    return parent[node];
}

int LCA(int node1, int node2){
    // level 일치시키기(낮추기)
    if(level[node1] != level[node2]){
        int dif = abs(level[node1] - level[node2]);
        if(level[node1] < level[node2]){
            for(int i = 0; i < dif; i++){
                node2 = UP(node2);
            }
        }
        else{
            for(int i = 0; i < dif; i++){
                node1 = UP(node1);
            }
        }
    }
    
    while(node1 != node2){
        node1 = UP(node1);
        node2 = UP(node2);
    }
    return node1;
}


int main(){
    int n; 
    cin >> n;
    vector<vector<int>> Tree(n + 1);
    for(int i = 1; i < n; i++){
        int n1, n2;
        cin >> n1 >> n2;
        Tree[n1].push_back(n2);
        Tree[n2].push_back(n1);
    }
    visit[1] = true;
    level[1] = 0;
    parent[1] = 1;
    deque<int> dq = {1};
    while(!dq.empty()){ // 사전작업 : BFS로 돌며 각 노드의 level(depth)가 몇인지, parent는 누구인지 기록
        int pn = dq.front();
        dq.pop_front();
        for(int pn_child : Tree[pn]){
            if(!visit[pn_child]){
                visit[pn_child] = true;
                level[pn_child] = level[pn] + 1;
                parent[pn_child] = pn;
                dq.push_back(pn_child);   
            }
        }
    }
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        int n1, n2;
        cin >> n1 >> n2;
        cout << LCA(n1, n2) << "\n";
    }
}