#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*
1000000007을 출력이 아니라 계속 나눠야함
*/
int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> dp(N+1,0);
    dp[0]=1;
    for(int i=1;i<=N;i++)
    {
        dp[i]=dp[i-1];
        if(i>=M)
        {
            dp[i]+=dp[i-M];
        }
        dp[i]%=1000000007;
    }
    cout<<dp[N];
    return 0;
}