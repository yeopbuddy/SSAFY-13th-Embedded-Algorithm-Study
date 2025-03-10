#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
vector<vector<int>> list;
vector<int> dp;

bool cmp(vector<int>& a, vector<int>& b)
{
    return a[0]<b[0];
}
int main()
{
    fastio;
    int n;
    cin >> n;
    list.resize(n);
    for (int i = 0; i < n; i++)
    {
        list[i].resize(2);
        cin >> list[i][0] >> list[i][1];
    }
    sort(list.begin(),list.end(),cmp);      //왼쪽 기준 정렬

    dp.resize(n,1);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(list[i][1]>list[j][1])           //이전 리스트에서 작은 값이 있다면
            {
                dp[i]=max(dp[i],dp[j]+1);       //현재 있는 값이랑 작은값의+1과 비교
            }
        }
    }
    int m=0;
    for(auto& li:dp)
    {
        if(li>m)
        {
            m=li;
        }
    }
    cout<<n-m;
    return 0;
}

/*
0 1 2 3 4 5 6 7
8 2 9 1 4 6 7 10






*/
