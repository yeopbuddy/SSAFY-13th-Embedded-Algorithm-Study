#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
vector<vector<int>> cost;       //값 배열
vector<vector<int>> dp[2];      //0은 > 1은 <
int main()
{
    fastio;
    int n, m;
    cin >> n >> m;
    cost.resize(n, vector<int>(m, 0));      //초기화
    dp[1] = dp[0] = cost;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> cost[i][j];
        }
    }
    dp[0][0][0]=cost[0][0];                 //처음 0,0 고정
    for (int j = 1; j < m; j++)
    {
        dp[0][0][j]=dp[0][0][j-1] + cost[0][j];
    }
    for (int i = 1; i < n; i++)
    {
        dp[0][i][0]=dp[0][i-1][0]+cost[i][0];           //위의 값+현재값
        dp[1][i][m-1]=dp[0][i-1][m-1]+cost[i][m-1];
        for (int j = 1; j < m; j++)                     //dp
        {
            dp[0][i][j]=max(dp[0][i-1][j],dp[0][i][j-1])+cost[i][j];
        }
        for (int j = m-2; j >=0; j--)
        {
            dp[1][i][j]=max(dp[0][i-1][j],dp[1][i][j+1])+cost[i][j];
        }
        for (int j = 0; j < m; j++)                     //왼 오 최대값값
        {
            dp[0][i][j]=max(dp[0][i][j],dp[1][i][j]);
        }
    }
    // for(int i=0;i<n;i++)
    // {
    //     for(int j=0;j<m;j++)
    //     {
    //         cout<<dp[0][i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout<<dp[0][n-1][m-1];
    return 0;
}

/*




*/
