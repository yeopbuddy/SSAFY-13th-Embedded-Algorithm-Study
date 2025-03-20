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
vector<vector<int>> list;
int count(int x)
{
    if(node[x])                 //값이 있을경우 해당값 가져오기
    {
        return node[x];         
    }
    node[x]=1;                  //방문처리+ 자기자신도 포함임으로 1부터 시작
    for(auto li : list[x])      //연결되어 있는 노드탐색
    {
        if(node[li])            //값이 있을경우 탐색x
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
    node.resize(n+1);           
    list.resize(n+1);
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
        cout<<node[x]<<endl;     //나온값 호출
    }
    return 0;
}

/*

*/