#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
vector<int> dp;
vector<vector<int>> list;
/*
가지중 가장 시간이 많이 걸리는 순서대로 선택(pq사용)
가지에 걸리는 시간+ 오래걸리는 순서대로 했을때 해당 가지에 선택한 시간의 최대값
*/
void tdp(int n)
{
    priority_queue<int> pq;
    dp[n]=list[n].size();           //자식노드 없으면 0 아니면 자식노드의 dp가 1로 가정하고 시작
    for(auto& li: list[n])
    {
        if(dp[li]<0)                //아직 계산 안된 dp 계산
        {
            tdp(li);
        }
        pq.push(dp[li]);
    }
    int idx=1;
    while(!pq.empty())              //값이 가장 큰것부터
    {
        dp[n]=max(dp[n],idx+pq.top());
        pq.pop();
        idx++;
    }
}
int main()
{
    int n,x;
    cin >> n;
    list.resize(n);
    dp.resize(n,-1);
    cin>>x;
    for(int i=1;i<n;i++)
    {
        cin >> x;
        list[x].push_back(i);
    }
    tdp(0);
    cout<<dp[0];
    return 0;
}
