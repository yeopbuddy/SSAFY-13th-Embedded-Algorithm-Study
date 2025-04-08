#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> list;
    int t, w, in, prv = 1, count = 0;
    cin >> t >> w;
    for (int i = 0; i < t; i++)
    {
        cin >> in;
        if (prv == in)
        {
            count++;
        }
        else
        {
            list.push_back(count);
            prv = in;
            count = 1;
        }
    }
    list.push_back(count);

    int sizelist = list.size() - 1;
    int dp[1001][31] = {0};
    int num = 0;

    if (sizelist == 0)
    {
        cout << list[0];
        return 0;
    }

    dp[0][0] = list[0];
    dp[1][1] = list[1] + dp[0][0];
    for (int i = 2; i <= sizelist; i++)
    {
        for (int j = i; j >= 1; j -= 2)
        {
            dp[i][j] = max(dp[i - 2][j], dp[i - 1][j - 1]) + list[i];
        }
        if (i % 2 == 0)
        {
            dp[i][0] = dp[i - 2][0] + list[i];
        }
    }
    for (int i = 0; i <= w; i++)
    {
        num = max(num, dp[sizelist][i]);
        num = max(num, dp[sizelist - 1][i]);
    }
    cout << num;
    return 0;
}
