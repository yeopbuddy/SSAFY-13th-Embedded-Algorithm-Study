#include <vector>
#include <iostream>
#include <algorithm>

#include <climits>

#define TRUE (1)
#define FALSE (0)

using namespace std;

class Book
{
private:
    int ch_num;
    vector<int> ch_size_arr;
    // ch.1 ~ch.idx 까지 합
    vector<int> prefix_sum_arr;
    // DP[N][M] = ch.N ~ch.M 까지 병합하기 위한 최소 비용
    vector<vector<int>> DP;
    void initTable()
    {
        for (int i = 0; i <= ch_num; i++)
            DP[i][i] = 0;

        prefix_sum_arr[0] = ch_size_arr[0];
        for (int i = 1; i <= ch_num; i++)
        {
            prefix_sum_arr[i] = ch_size_arr[i] + prefix_sum_arr[i - 1];
        }
    }

    int getPrefixSum(int s, int e)
    {
        return prefix_sum_arr[e] - prefix_sum_arr[s - 1];
    }

    void updateDP(int s, int e)
    {
        int cost = getPrefixSum(s, e);
        for (int i = s; i < e; i++)
            DP[s][e] = min(DP[s][e], DP[s][i] + DP[i + 1][e] + cost);
    }

public:
    Book(int cn) : ch_num(cn), ch_size_arr(cn + 1), prefix_sum_arr(cn + 1), DP(cn + 1, vector<int>(cn + 1, INT_MAX))
    {
        ch_size_arr[0] = 0;
        for (int i = 1; i <= ch_num; i++)
            cin >> ch_size_arr[i];
    }

    int merge()
    {
        initTable();
        for (int i = 1; i <= ch_num; i++)
            for (int l = i; l >= 1; l--)
                updateDP(l, i);
        return DP[1][ch_num];
    }

    void printDP()
    {
        for (int i = 1; i <= ch_num; i++)
        {
            for (int l = 1; l <= ch_num; l++)
                cout << DP[i][l] << ' ';
            cout << endl;
        }
    }
};

int main(void)
{
    int T;
    cin >> T;
    for (int tc = 0; tc < T; tc++)
    {
        int K;
        cin >> K;
        Book m(K);
        int answer = m.merge();
        // m.printDP();
        cout << answer << endl;
    }

    return 0;
}