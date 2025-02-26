#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(void)
{
    int S;
    cin >> S;
    //0: 직전 계단을 안 밣을때 최대, 1: 직전 계단을 밣을때 최대
    vector<vector<int>> DP(2,vector<int>(S+1,0));
    vector<int> input(S+1);

    for(int i = 1;i<=S;i++)
        cin >> input[i];

    DP[0][1] = input[1];
    for(int i= 2;i<=S;i++)
    {
        DP[0][i] = input[i] + max(DP[0][i-2],DP[1][i-2]);
        DP[1][i] = input[i] + DP[0][i-1];
    }

    cout<<max(DP[0][S],DP[1][S]);

    return 0;
}