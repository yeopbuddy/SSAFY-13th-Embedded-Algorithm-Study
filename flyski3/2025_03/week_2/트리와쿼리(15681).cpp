#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
#define endl '\n';
int n,r,q;
vector<int> node;
vector<int> vist;
vector<vector<int>> list;
int count(int x)
{
    if(node[x])
    {
        return node[x];         //이미 구한 값이면 리턴
    }
    node[x]=1;                  //자기 자신도 포함
    vist[x]=1;                  //방문처리
    for(auto li : list[x])      //연결되어 있는 노드탐색
    {
        if(vist[li])            //방문처리 되어있으면 탐색x
        {
            continue;
        }
        else
        {
            node[x]+=count(li);  //재귀후 그값 더하기
        }
    }
    return node[x];
}
int main()
{
    fastio;
    cin >> n >> r >>q;
    node.resize(n+1);           //가시성을 위해 1부터
    list.resize(n+1);
    vist.resize(n+1);
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin >> x >>y;
        list[x].push_back(y);   //양방향 연결
        list[y].push_back(x);
    }
    count(r);                   //루트 정해서 구하기
    for(int i=0;i<q;i++)
    {
        int x;
        cin >> x;
        cout<<node[x]<<endl;     //나온값 호출출
    }
    return 0;
}

/*

*/