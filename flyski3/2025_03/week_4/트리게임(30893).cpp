#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n,s,e;
vector<vector<int>> list;
vector<int> vist;
vector<int> parent;
void dfs(int node)
{
    vist[node]=1;
    for(int next : list[node])
    {
        if(!vist[next]) //자식의 부모는 자신
        {
            parent[next]=node;
            dfs(next);
        }
    }
}
void pt(vector<int>& path,int start,int end)
{
    for(int node = end;node!=start;node=parent[node])
    {
        path.push_back(node);
    }
    path.push_back(start);
    reverse(path.begin(),path.end());
}
int main() {
    cin>>n>>s>>e;
    list.resize(n+1);
    vist.resize(n+1);
    parent.resize(n+1);

    for(int i=1;i<n;i++)
    {
        int a,b;
        cin >> a >>b;
        list[a].push_back(b);       //양방향
        list[b].push_back(a);
    }
    dfs(s);                         //루트를 기준으로 트리
    vector<int> path;
    pt(path,s,e);           //e부터 s까지 부모를 쫒아가면서 배열 확인
    for(int i=1;i<path.size();i++)
    {
        if(path[i]==e)
        {
            break;
        }
        if(i%2&&list[path[i]].size()>2) //홀수면서 다른 곳으로 갈 수 있다면 패배
        {
            cout<<"Second";
            return 0;
        }
    }
    cout<<"First";
    return 0;
}
