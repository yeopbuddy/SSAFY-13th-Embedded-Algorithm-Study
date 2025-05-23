#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
/*
채굴(15573)과 비슷하게 해결(다이스트라)
방문처리는 0 -> 가장 낮은 값이 1이기 때문에 1로 초기화
방문처리(0)이면 건뛰, 크다면 해당 레벨로 큐에 넣기
작은 경우 현재레벨과 해당 레벨의 차를 val에 합산 후 현재 레벨로 큐에 넣기
-> 방문처리(값은 큐에 적재해둔 상태)
*/
struct node
{
    int x, y;
    int level;
    bool operator<(const node &other) const
    {
        return level > other.level;
    }
};
int xy[4][2] = {
    -1, 0,
    0, 1,
    1, 0,
    0, -1};
int bfs(vector<vector<int>> &pool, int n, int m)
{
    int val = 0;
    priority_queue<node> qu;
    qu.push({0, 0, 1});
    pool[0][0] = 0;
    while (!qu.empty())
    {
        node temp = qu.top();
        qu.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = temp.x + xy[i][0];
            int y = temp.y + xy[i][1];
            if (x < 0 || y < 0 || x > n + 1 || y > m + 1)
            {
                continue;
            }
            else if (pool[x][y] == 0)
            {
                continue;
            }
            else
            {
                if (pool[x][y] >= temp.level)
                {
                    qu.push({x, y, pool[x][y]});
                }
                else
                {
                    qu.push({x, y, temp.level});
                    val += temp.level - pool[x][y];
                }
                pool[x][y] = 0;
            }
        }
    }
    return val;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> pool(n + 2, vector<int>(m + 2, 1));
    for (int i = 1; i <= n; i++)
    {
        string temp;
        cin >> temp;
        for (int j = 0; j < m; j++)
        {
            pool[i][j + 1] = temp[j] - '0';
        }
    }
    cout << bfs(pool, n, m);
    return 0;
}
