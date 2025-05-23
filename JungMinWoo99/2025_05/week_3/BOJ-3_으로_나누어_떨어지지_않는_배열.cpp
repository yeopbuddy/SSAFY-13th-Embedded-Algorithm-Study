#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

#include <deque>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> mod3[3];

    int N;
    cin >> N;
    for (int idx = 0; idx < N; idx++)
    {
        int input;
        cin >> input;
        mod3[input % 3].push_back(input);
    }

    deque<int> answer;
    if (!mod3[0].empty())
    {
        answer.push_back(mod3[0].back());
        mod3[0].pop_back();
    }
    else if (!mod3[1].empty() && !mod3[2].empty())
    {
        cout << -1 << endl;
        return 0;
    }
    while (!mod3[0].empty() || !mod3[1].empty() || !mod3[2].empty())
    {

        if (!mod3[1].empty())
        {
            answer.push_back(mod3[1].back());
            mod3[1].pop_back();
        }
        else if (!mod3[2].empty())
        {
            answer.push_front(mod3[2].back());
            mod3[2].pop_back();
        }

        if (!mod3[0].empty() && answer.back() % 3 != 0)
        {
            answer.push_back(mod3[0].back());
            mod3[0].pop_back();
        }

        if (!mod3[0].empty() && answer.front() % 3 != 0)
        {
            answer.push_front(mod3[0].back());
            mod3[0].pop_back();
        }

        if (mod3[1].empty() && mod3[2].empty() && !mod3[0].empty())
        {
            cout << -1 << endl;
            return 0;
        }
    }

    for (auto &ele : answer)
        cout << ele << ' ';

    return 0;
}