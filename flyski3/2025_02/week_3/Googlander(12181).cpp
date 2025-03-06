#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
vector<vector<int>> vist;
int mx, my;
long long dp[26][26];

long long dpp(int x,int y)
{
    if(x==1||y==1) {return 1;} //x나 y가 1일경우 한가지 길밖에 없음
    long long sum=0;
    if(dp[x][y])                //만약 이전에 구했던 값이면 그값 리턴(시간절약)
        return dp[x][y];
    for(int i=1;i<=x;i++)       //아니면 새로 구해야함
        sum+=dpp(i,y-1); 
    dp[x][y]=sum;               //그 값 기록
    return sum;
}
int main()
{
    fastio;
    int n;
    cin >> n;
    for(int i=1;i<26;i++)   //dp배열 초기화화
    {
        for(int j=1;j<26;j++)
        {
            dp[i][j]=0;
        }
    }
    for (int tc = 1; tc <= n; tc++)
    {
        cin >> mx >> my;
        cout<<"Case #"<< tc <<": "<<dpp(mx,my)<<endl;
    }
    return 0;
}