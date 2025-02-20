#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
int n;
int sum[501],list[501],dp[501][501];
int main()
{
    fastio;
    int testcases;
    cin >> testcases;
    for (int cases=0; cases < testcases; cases++)
    {
        sum[0]=0;
        cin >> n;
        for(int i=1;i<=n;i++)
        {
            cin>>list[i];
            sum[i]=sum[i-1]+list[i];        //빠른 계산을 위한 누적합
        }
        for(int i=1;i<=n;i++)   //최소 x,x+1 2개/최대 x,x+n까지 비교
        {
            for(int x=1;x<=n-i;x++) //x를 인덱스로 비교
            {
                int y=x+i;
                dp[x][y]=1e9;
                for(int k=x;k<y;k++)    //부분으로 나눠서 구하기기
                {
                    dp[x][y]=min(dp[x][y],dp[x][k]+dp[k+1][y]+sum[y]-sum[x-1]); //x~y구간 누적합+dp
                }
            }
        }
        cout<<dp[1][n]<<endl;
    }
    return 0;
}
/*

40 30
      30 50
40 30 30 50     300

   30 30
40 30 30
40 30 30 50     310

40 30
      30 100
40 30 30 100    400

   30 30
40 30 30
40 30 30 100    360



*/
