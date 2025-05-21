#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n,m,st,en,val;
    cin >> n>>m;
    vector<vector<int>> dp(n+1,vector<int>(n+1,300));
    for(int i=1;i<=n;i++)
    {
        dp[i][i]=0;
    }
    for(int i=0;i<m;i++)
    {
        cin>>st>>en>>val;
        if(val)
        {
            dp[st][en]=0;
            dp[en][st]=0;
        }
        else
        {
            dp[st][en]=0;
            dp[en][st]=min(dp[en][st],1);
        }
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dp[i][k] < 300 && dp[k][j] < 300)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    int k;
    cin >> k;
    for(int i=0;i<k;i++)
    {
        int st,en;
        cin>>st>>en;
        cout<<dp[st][en]<<endl;
    }
    return 0;
}
