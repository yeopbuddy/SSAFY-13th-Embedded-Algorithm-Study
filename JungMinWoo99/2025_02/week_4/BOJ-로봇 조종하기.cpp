#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

#define endl '\n'
using namespace std;

class Robot
{
public:
    Robot(int N, int M) : row_size(N), col_size(M), input(N, vector<int>(M, 0)), DP(N, vector<int>(M, 0))
    {
        for (auto &row : input)
            for (auto &i : row)
                cin >> i;
    }

    int FindMaxValue()
    {
        DP[0][0] = input[0][0];
        for (int i = 1; i < col_size; i++)
            DP[0][i] = input[0][i] + DP[0][i - 1];

        for (int i = 1; i < row_size; i++)
        {
            vector<int> dp_left(col_size);
            dp_left[0] = DP[i - 1][0] + input[i][0];
            for (int l = 1; l < col_size; l++)
                dp_left[l] = max(dp_left[l - 1], DP[i - 1][l]) + input[i][l];
            vector<int> dp_right(col_size);
            dp_right[col_size - 1] = DP[i - 1][col_size - 1] + input[i][col_size - 1];
            for (int l = col_size - 2; l > -1; l--)
                dp_right[l] = max(dp_right[l + 1], DP[i - 1][l]) + input[i][l];
            for (int l = 0; l < col_size; l++)
                DP[i][l] = max(dp_left[l], dp_right[l]);
        }

        return DP[row_size - 1][col_size - 1];
    }

private:
    int row_size, col_size;
    vector<vector<int>> input;
    vector<vector<int>> DP;

    bool checkBound(int y, int x)
    {
        return -1 < y && y < row_size && -1 < x && x < col_size;
    }
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    Robot bot(N, M);
    cout << bot.FindMaxValue();
}