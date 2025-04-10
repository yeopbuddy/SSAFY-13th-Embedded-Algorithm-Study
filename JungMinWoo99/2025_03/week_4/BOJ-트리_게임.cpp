#include <iostream>
#define endl '\n'

#include <vector>
#include <queue>

using namespace std;

class Tree
{
public:
    Tree(int N, int S, int E) : node_num(N), start(S), end(E), abj_list(N + 1) {}

    void AddEdges(int u, int v)
    {
        abj_list[u].push_back(v);
        abj_list[v].push_back(u);
    }

    bool CanFirstWin()
    {
        dfs(start);
        bool first_win = true;
        for (int idx = 0; idx < dfs_stack.size()-1; idx++)
            if (idx % 2 == 1)// 후공에서 목표까지 가는 길 이외 길이 있으면 선공 패배
                first_win &= (abj_list[dfs_stack[idx]].size() <= 2); 
        return first_win;
    }

private:
    int node_num;
    int start, end;
    vector<vector<int>> abj_list;
    vector<int> dfs_stack;

    bool dfs(int cur)
    {
        int p_node = -1;
        if (!dfs_stack.empty())
            p_node = dfs_stack.back();
        dfs_stack.push_back(cur);

        if (cur == end)
            return true;

        for (int c_node : abj_list[cur])
            if (c_node != p_node)
                if (dfs(c_node))//목표 노드까지 경로를 찾았으면 탐색 중단
                    return true;

        dfs_stack.pop_back();
        return false;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, S, E;
    cin >> N >> S >> E;
    Tree tree(N, S, E);
    for (int e = 0; e < N - 1; e++)
    {
        int u, v;
        cin >> u >> v;
        tree.AddEdges(u, v);
    }

    if(tree.CanFirstWin())
        cout<<"First"<<endl;
    else
        cout<<"Second"<<endl;

    return 0;
}