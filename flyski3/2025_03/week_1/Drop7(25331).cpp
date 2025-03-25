#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
struct xy
{
    int garo = 0;
    int sero = 0;
    int val = 0;
};
int miny=10000;
vector<vector<xy>> map_drop;
int n, m;
void down(vector<vector<xy>> &map_copy)
{
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            if (map_copy[i][j].val) // 0이 아니면 garo,sero
            {
                int idx = i + 1;
                while (idx < n && !map_copy[idx][j].val)
                {
                    idx++;
                }
                if (idx > i + 1)
                {
                    map_copy[idx - 1][j].val = map_copy[i][j].val;
                    map_copy[i][j].val = 0;
                }
            }
        }
    }
}
void set(vector<vector<xy>> &map_copy)
{
    down(map_copy);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map_copy[i][j].garo = map_copy[i][j].sero = 0;
            if (map_copy[i][j].val) // 0이 아니면 garo,sero
            {
                if (i >= 1 && map_copy[i - 1][j].sero) // 세로는 빈칸이 없기때문에 해당 열은 다 같음
                {
                    map_copy[i][j].sero = map_copy[i - 1][j].sero;
                }
                else
                {
                    map_copy[i][j].sero = 7 - i;
                }
                if (j >= 1 && map_copy[i][j - 1].garo) // 왼쪽에서 연결된 가로를 구하기 때문에 불러오기
                {
                    map_copy[i][j].garo = map_copy[i][j - 1].garo;
                }
                else // 오른쪽 값이 0이 아닐경우 체크
                {
                    int idx = 1;
                    while (j + idx < n && map_copy[i][j + idx].val)
                    {
                        idx++;
                    }
                    map_copy[i][j].garo = idx;
                }
            }
        }
    }
    return;
}
bool boom(vector<vector<xy>> &map_copy)
{
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map_copy[i][j].val)
            {
                if (map_copy[i][j].val == map_copy[i][j].garo)
                {
                    flag = true;
                    map_copy[i][j].val = 0;
                }
                else if (map_copy[i][j].val == map_copy[i][j].sero)
                {
                    flag = true;
                    map_copy[i][j].val = 0;
                }
            }
        }
    }
    set(map_copy);
    return flag;
}
void go(vector<vector<xy>> map_copy,int i)
{
    int con=0;
    map_copy[0][i].val=m;
    set(map_copy);
    while (boom(map_copy))
    {
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(map_copy[i][j].val)
            {
                con++;
            }
        }
    }
    if(miny>con)
    {
        miny=con;
    }
    return;
}
int main()
{
    fastio;
    // cin >> n;
    n = 7;
    map_drop.resize(n, vector<xy>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map_drop[i][j].val;
        }
    }
    cin >> m;
    for(int i=0;i<n;i++)
    {
        go(map_drop,i);
    }
    cout<<miny;
    return 0;
}