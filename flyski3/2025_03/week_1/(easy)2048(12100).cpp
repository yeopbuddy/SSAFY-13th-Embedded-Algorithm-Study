#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
vector<vector<int>> map_2048;
int n;
int max_num = 0;

// 완탐으로 맥스값 체크
void chk(vector<vector<int>> &li)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (li[i][j] > max_num)
            {
                max_num = li[i][j];
            }
        }
    }
    return;
}

/*
j=붙는 방향부터 출발하는 인덱스
k=합칠수 있는 인덱스 / 0일경우 이동


0 4 2 1 k=0 j=1     k=0 > j>>k
4 0 2 1 k=0 j=2     k!=0 & k!=j > k++ > j>>k
4 2 0 1 k=1 j=3     k!=0 & k!=j > k++ > j>>k

4 2 1 0 1 2 4   k=2 j=4     > k!=0 & k==j > k*2 > k++
4 2 2 0 0 2 4   k=3 j=5     > k=0 > j>>k
4 2 2 2 0 0 4   k=3 j=6     > k!=0 & k!=j > k++ > j>>k

0일경우 패스
만약 k!=j 라서 옮길때 ++k==j라면 이동x

dfs로 배열 넘겨서 4^5번 탐색
*/

void shk(vector<vector<int>> li, int num, int st)
{
    if (st == 1)
    {
        for (int i = 0; i < n; i++)
        {
            int k = 0;
            for (int j = 1; j < n; j++)
            {
                if (li[i][j] == 0)
                {
                    continue;
                }
                if (li[i][k] == 0)
                {
                    li[i][k] = li[i][j];
                    li[i][j] = 0;
                }
                else if (li[i][k] == li[i][j])
                {
                    li[i][k] *= 2;
                    li[i][j] = 0;
                    k++;
                }
                else
                {
                    k++;
                    if (j != k)
                    {
                        li[i][k] = li[i][j];
                        li[i][j] = 0;
                    }
                }
            }
        }
    }
    else if (st == 2)
    {
        for (int i = 0; i < n; i++)
        {
            int k = n - 1;
            for (int j = n - 2; j >= 0; j--)
            {
                if (li[i][j] == 0)
                {
                    continue;
                }
                if (li[i][k] == 0)
                {
                    li[i][k] = li[i][j];
                    li[i][j] = 0;
                }
                else if (li[i][k] == li[i][j])
                {
                    li[i][k] *= 2;
                    li[i][j] = 0;
                    k--;
                }
                else
                {
                    k--;
                    if (j != k)
                    {
                        li[i][k] = li[i][j];
                        li[i][j] = 0;
                    }
                }
            }
        }
    }
    else if (st == 3)
    {
        for (int j = 0; j < n; j++)
        {
            int k = 0;
            for (int i = 1; i < n; i++)
            {
                if (li[i][j] == 0)
                {
                    continue;
                }
                if (li[k][j] == 0)
                {
                    li[k][j] = li[i][j];
                    li[i][j] = 0;
                }
                else if (li[k][j] == li[i][j])
                {
                    li[k][j] *= 2;
                    li[i][j] = 0;
                    k++;
                }
                else
                {
                    k++;
                    if (i != k)
                    {
                        li[k][j] = li[i][j];
                        li[i][j] = 0;
                    }
                }
            }
        }
    }
    else if (st == 4)
    {
        for (int j = 0; j < n; j++)
        {
            int k = n - 1;
            for (int i = n - 2; i >= 0; i--)
            {
                if (li[i][j] == 0)
                {
                    continue;
                }
                if (li[k][j] == 0)
                {
                    li[k][j] = li[i][j];
                    li[i][j] = 0;
                }
                else if (li[k][j] == li[i][j])
                {
                    li[k][j] *= 2;
                    li[i][j] = 0;
                    k--;
                }
                else
                {
                    k--;
                    if (i != k)
                    {
                        li[k][j] = li[i][j];
                        li[i][j] = 0;
                    }
                }
            }
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << li[i][j];
    //     }
    //     cout << endl;
    // }
    // return;
    if (num >= 5)
    {
        chk(li);
        return;
    }
    for (int i = 1; i <= 4; i++)
    {
        shk(li, num + 1, i);
    }
    return;
}
int main()
{
    fastio;
    cin >> n;
    map_2048.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map_2048[i][j];
        }
    }
    shk(map_2048, 0, 0);
    cout << max_num;
    return 0;
}