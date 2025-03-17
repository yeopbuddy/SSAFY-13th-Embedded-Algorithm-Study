#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
string messi = "Messi";
string gimossi = "Gimossi";
long long dp[100];
long long n;
int main()
{
    fastio;
    cin >> n;
    dp[0] = gimossi.length();       //문자수
    dp[1] = messi.length();         //문자수
    int i = 1;                      //dp시작
    while (dp[i] < n)
    {
        i++;
        dp[i] = dp[i - 1] + 1 + dp[i - 2];
    }
    while (i>2)
    {
        i--;                        //역산
        if(n>dp[i])                 //만약 크면 빼기
        {
            n-=dp[i]+1;             //연결할때 쓴 " "도 제거
        }
    }
    messi = " "+messi+" "+gimossi;  //0번 인덱스는 빈칸
    if(messi[n]==' ')
    {
        cout<< "Messi"<<messi; 
    }
    else
        cout<< messi[n];
    return 0;
}