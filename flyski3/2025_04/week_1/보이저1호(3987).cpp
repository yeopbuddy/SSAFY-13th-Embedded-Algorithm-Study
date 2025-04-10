#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int n, m;
int xy[4][2] = {
    -1, 0,
    0, 1,
    1, 0,
    0, -1};
bool chk(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= m)
        return false;
    return true;
}
int launch(vector<vector<int>> sp, int x, int y, int dt)
{
    int cont = 0;
    while (chk(x, y))
    {
        if (sp[x][y] == -1)
        {
            return cont;
        }
        else if (sp[x][y] == -2) // u <=> r / d <=> l
        {
            if (dt == 0)
            {
                dt = 1;
            }
            else if (dt == 1)
            {
                dt = 0;
            }
            else if (dt == 2)
            {
                dt = 3;
            }
            else if (dt == 3)
            {
                dt = 2;
            }
        }
        else if (sp[x][y] == -3) // u <=> l / d <=> r
        {
            if (dt == 0)
            {
                dt = 3;
            }
            else if (dt == 3)
            {
                dt = 0;
            }
            else if (dt == 2)
            {
                dt = 1;
            }
            else if (dt == 1)
            {
                dt = 2;
            }
        }
        else if(sp[x][y] & (1<<dt))
        {
            return -5;
        }
        else
        {
            sp[x][y] |= (1<<dt);
        }
        x += xy[dt][0];
        y += xy[dt][1];
        cont++;
    }
    return cont;
}
int main()
{
    cin >> n >> m;
    vector<vector<int>> space(n, vector<int>(m)); // int로 바꾸고 1234 비트계산
    char x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            if (x == 'C')
            {
                space[i][j] = -1;
            }
            else if (x == '/') // u <=> r / d <=> l
            {
                space[i][j] = -2;
            }
            else if (x == '\\') // u <=> l / d <=> r
            {
                space[i][j] = -3;
            }
        }
    }
    char uplr[5] = {'U','R','D','L'};
    int pr, pc;
    int lc,dt,cm=0;
    cin >> pr >> pc;
    for (int i = 0; i < 4; i++)
    {
        lc=launch(space, pr - 1, pc - 1, i);
        if(lc==-5)
        {
            cout<<uplr[i]<<endl<<"Voyager";
            return 0;
        }
        if(cm<lc)
        {
            cm=lc;
            dt=i;
        }
    }
    cout<<uplr[dt]<<endl<<cm;
    return 0;
}
