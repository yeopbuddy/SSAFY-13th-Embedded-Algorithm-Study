#include <climits>
#include <iostream>
#include <vector>

using namespace std;

#define CH_LIM (4)

int main(void)
{
    int N;
    cin >> N;
    vector<int> in(N);
    // 초기값 설정
    for (int i = 0; i < N; i++)
        cin >> in[i];

    vector<vector<int>> DP(CH_LIM, vector<int>(N, 0));

    // 초기값 설정
    DP[0][0] = in[0];
    for (int i = 1; i < N; i++)
    {
        if (DP[0][i - 1] <= in[i])
            DP[0][i] = in[i];
        else
            DP[0][i] = INT_MAX;
    }

    for (int i = 1; i < CH_LIM; i++)
    {
        DP[i][0] = 1;
        for (int l = 1; l < N; l++)
            if (DP[i - 1][l - 1] > in[l] && DP[i][l - 1] <= in[l])
                DP[i][l] = in[l];
            else
                DP[i][l] = DP[i - 1][l - 1];
    }

    // for (auto &i : DP)
    // {
    //     for (auto &l : i)
    //         cout << l << ' ';
    //     cout << endl;
    // }

    if(DP[CH_LIM-1][N-1] != INT_MAX)
    {
        cout<<"YES"<<endl;
        int idx = 0;
        while(DP[idx][N-1] == INT_MAX)
            idx++;
        cout <<idx<<endl;
        for(int i = N-1;i>-1;i--)
        {
            if(DP[idx][i] != in[i])
            {
                cout << i + 1<<' '<<DP[idx][i]<<endl;
                idx--;
            }
        }
    }
    else
        cout<<"NO"<<endl;

    return 0;
}