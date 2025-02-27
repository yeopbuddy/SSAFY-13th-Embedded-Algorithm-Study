#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
vector<vector<int>> map;
int mx, my;
int block(int x, int y)
{
    int sum[11];            //1~2: 4 3~6: 3+1 7~10: ㄹ 0:ㅁ
    if (y + 3 < my) //----
    {
        sum[1] = map[x][y] + map[x][y + 1] + map[x][y + 2] + map[x][y + 3];
    }
    if (x + 3 < mx) //---- 세로
    {
        sum[2] = map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 3][y];
    }
    if (y + 2 < my) //---,위 아래
    {
        sum[0] = map[x][y] + map[x][y + 1] + map[x][y + 2];
        if (x + 1 < mx)
        {
            int max = map[x + 1][y];
            if (max < map[x + 1][y + 1])
                max = map[x + 1][y + 1];
            if (max < map[x + 1][y + 2])
                max = map[x + 1][y + 2];
            sum[3] = sum[0] + max;
            sum[7] = map[x][y] + map[x][y + 1] + map[x + 1][y + 1] + map[x + 1][y + 2];
        }
        else
        {
            sum[3] = 0;
            sum[7] = 0;
        }
        if (x > 0)
        {
            int max = map[x - 1][y];
            if (max < map[x - 1][y + 1])
                max = map[x - 1][y + 1];
            if (max < map[x - 1][y + 2])
                max = map[x - 1][y + 2];
            sum[4] = sum[0] + max;
            sum[8] = map[x][y] + map[x][y + 1] + map[x - 1][y + 1] + map[x - 1][y + 2];
        }
        else
        {
            sum[4] = 0;
            sum[8] = 0;
        }
    }

    if (x + 2 < mx) //--- 세로로, 좌 우
    {
        sum[0] = map[x][y] + map[x + 1][y] + map[x + 2][y];
        if (y + 1 < my)
        {
            int max = map[x][y + 1];
            if (max < map[x + 1][y + 1])
                max = map[x + 1][y + 1];
            if (max < map[x + 2][y + 1])
                max = map[x + 2][y + 1];
            sum[5] = sum[0] + max;
            sum[9] = map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y + 1];
        }
        else
        {
            sum[5] = 0;
            sum[9] = 0;
        }
        if (y > 0)
        {
            int max = map[x][y - 1];
            if (max < map[x + 1][y - 1])
                max = map[x + 1][y - 1];
            if (max < map[x + 2][y - 1])
                max = map[x + 2][y - 1];
            sum[6] = sum[0] + max;
            sum[10] = map[x][y] + map[x + 1][y] + map[x + 1][y - 1] + map[x + 2][y - 1];
        }
        else
        {
            sum[6] = 0;
            sum[10] = 0;
        }
    }
    if (x + 1 < mx && y + 1 < my)       //박스
    {
        sum[0] = map[x][y] + map[x][y + 1] + map[x + 1][y] + map[x + 1][y + 1];
    }
    int max = 0;
    for (int i = 0; i < 11; i++)       
    {
        if (max < sum[i])
        {
            max = sum[i];
        }
    }
    return max;
}
int main()
{
    fastio;
    cin >> mx >> my;
    map.resize(mx, vector<int>(my, 0));
    for (int i = 0; i < mx; i++)
    {
        for (int j = 0; j < my; j++)
        {
            cin >> map[i][j];
        }
    }
    int max = 0;
    for (int i = 0; i < mx; i++)
    {
        for (int j = 0; j < my; j++)
        {
            int x = block(i, j);    //해당 칸의 max
            if (max < x)
                max = x;
        }
    }
    cout << max;
    return 0;
}