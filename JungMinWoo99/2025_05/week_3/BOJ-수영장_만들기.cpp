#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

#include <queue>

using namespace std;

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

class SwimmingPool
{
public:
    SwimmingPool(int N, int M) : n(N), m(M), input_pool(N, vector<int>(M))
    {
        for (auto &row : input_pool)
            for (auto &ele : row)
            {

                char ch;
                do
                {
                    ch = cin.get();
                } while (ch == '\n');
                ele = ch - '0';
            }

        full_pool = input_pool;
    }

    void FillPool()
    {
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                for (int p = input_pool[r][c] + 1; p < 10; p++)
                {
                    if (CanPour(p, r, c))
                        full_pool[r][c] = p;
                    else
                        break;
                }
    }

    int GetAnswer()
    {
        // for (auto &row : full_pool)
        // {
        //     for (auto &ele : row)
        //         cout << ele;
        //     cout << endl;
        // }
        int answer = 0;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                answer += full_pool[r][c] - input_pool[r][c];
        return answer;
    }

private:
    int n, m;
    vector<vector<int>> input_pool;
    vector<vector<int>> full_pool;

    bool CanPour(int p, int r, int c)
    {
        vector<vector<int>> is_visited(n, vector<int>(m, false));
        queue<pair<int, int>> bfs_que;
        bfs_que.push({r, c});
        is_visited[r][c] = true;
        while (!bfs_que.empty())
        {
            auto cur_pos = bfs_que.front();
            bfs_que.pop();
            for (int dir = 0; dir < 4; dir++)
            {
                pair<int, int> next_pos = {cur_pos.first + dy[dir], cur_pos.second + dx[dir]};
                if (!IsNotFlood(next_pos.first, next_pos.second))
                    return false;
                else if (!is_visited[next_pos.first][next_pos.second] && p > input_pool[next_pos.first][next_pos.second])
                {
                    bfs_que.push(next_pos);
                    is_visited[next_pos.first][next_pos.second] = true;
                }
            }
        }
        return true;
    }

    bool IsNotFlood(int r, int c)
    {
        return -1 < r && r < n && -1 < c && c < m;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N, M;
    cin >> N >> M;
    SwimmingPool sp(N, M);
    sp.FillPool();
    int answer = sp.GetAnswer();
    cout << answer << endl;
    return 0;
}