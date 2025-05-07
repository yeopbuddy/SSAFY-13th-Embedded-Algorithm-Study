#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

constexpr int max_num = 1 << 15;
using namespace std;

vector<int> case_num_table(max_num, 0);
vector<int> square_num_table;

void FillSquareNumTable()
{
    square_num_table.push_back(0);
    for (int num = 1; num * num < max_num; num++)
        square_num_table.push_back(num * num);
}

void CountAllCase(int num_cnt = 4, int prev_idx = 0, int prefix_sum = 0)
{
    if (num_cnt == 0)
    {
        if (prefix_sum < max_num)
            case_num_table[prefix_sum]++;
        return;
    }
    for (int idx = prev_idx; idx < square_num_table.size(); idx++)
    {
        CountAllCase(num_cnt-1, idx, prefix_sum + square_num_table[idx]);
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    FillSquareNumTable();
    CountAllCase();

    while (true)
    {
        int input;
        cin >> input;
        if (input > 0)
            cout << case_num_table[input] << endl;
        else
            break;
    }

    return 0;
}