#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
int n, h;
vector<int> train;          //값
vector<vector<int>> dp;     //dp
int main()
{
    fastio;
    cin >> n;
    n++;
    train.resize(n);
    dp.resize(n,vector<int>(3,0));
    for (int i = 1; i < n; i++)
    {
        cin >> train[i];
        train[i]+=train[i-1];               //누적합 사용
    }
    cin >> h;                               //열차가 움직일 수 있는 수
    dp[h][0]=train[h]-train[0];             //기본값
    for(int i=h+1;i<n;i++)
    {
        dp[i][0]=max(train[i]-train[i-h],dp[i-1][0]);
        dp[i][1]=max(train[i]-train[i-h]+dp[i-h][0],dp[i-1][1]);
        dp[i][2]=max(train[i]-train[i-h]+dp[i-h][1],dp[i-1][2]);
    }
    cout<<dp[n-1][2]<<endl;
    
    return 0;
}


/*
범위 합계는 누적합 이용
편의를 위해 앞에 데이터 0추가

dp[h][1]=data[1~h]
dp[h][1]=max(data[1~h],dp[현재-h][1])
dp[2h][2]=data[h+1~2h]+dp[h][1]
dp[2h][2]=(data[h+1~2h]+dp[h][1],dp[2h][2])
dp[n-1][3]=data[n-1]~data[n-h]+dp[n-h-1][2],dp[n-2][3]
*/