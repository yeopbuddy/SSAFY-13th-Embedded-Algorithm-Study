#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;

struct xp
{
    int x,y;
    xp(int x,int y):x(x),y(y){}
    xp()=default;
    /* data */
};                          ///큐 구조체

int map[101][101]={0};      //맵
int vist[101][101]={0};     //방문
queue<xp> qu;               //큐
int n;
int xy[4][2] = {            //xy
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}};
int land = 2;               //섬 번호

void vclear()               //방문배열 초기화
{
    memset(vist,0,sizeof(vist));
}

void bfs(int x, int y, int ch)
{
    vclear();
    int dx, dy,nx,ny;
    int con = 0;
    qu.emplace(x, y);           //큐에 넣고 방문체크
    vist[x][y] = 1;
    while (!qu.empty())
    {
        int size=qu.size();     //flowfill
        for(int j=0;j<size;j++)
        {
            nx = qu.front().x;
            ny = qu.front().y;
            qu.pop();
            for (int i = 0; i < 4; i++)
            {
                 dx= nx + xy[i][0];
                 dy= ny + xy[i][1];
                if (dx < 0 || dy < 0 || dx >= n || dy >= n)
                {
                    continue;
                }
                if (map[dx][dy] == 0 && vist[dx][dy] == 0)              //만약 0(바다) and 방문하지 않으면 큐입력
                {
                    qu.emplace(dx, dy);
                    vist[dx][dy] = 1;
                }
                else if (map[dx][dy] != ch && map[dx][dy] != -ch && vist[dx][dy] == 0)  //만약 같은 섬(ch)and같은섬의 가장자리(-ch) and 방문하지 않으면 = 다른섬
                {
                    if (land > con)
                        land = con;
                    qu = queue<xp>();
                    return;
                }
            }
        }
        con++;
    }
    return;
}

void mc(int x, int y)
{
    int dx, dy,nx,ny;
    qu.emplace(x, y);
    vist[x][y]=1;
    while (!qu.empty())
    {
        nx = qu.front().x;
        ny = qu.front().y;
        qu.pop();
        map[nx][ny] = land;  // land기본값 1(++)
        for (int i = 0; i < 4; i++)
        {
            dx = nx + xy[i][0];
            dy = ny + xy[i][1];
            
            if (dx < 0 || dy < 0 || dx >= n || dy >= n) // 범위 넘으면x
            {
                continue;
            }
            if (map[dx][dy] == 1&&vist[dx][dy]==0) // 만약 같은 그룹이면
            {
                qu.emplace(dx, dy);
                vist[dx][dy]=1;
            }
            else if (map[dx][dy] == 0&&vist[dx][dy]==0) // 가장자리 처리(-land)
            {
                map[nx][ny]=-land;
            }
        }
    }
    land++;
    return;
}

int main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n; i++) // 입력
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < n; i++) // 섬별 그룹핑
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == 1)
            {
                mc(i, j);
            }
        }
    }
    land = 10000;           //min값으로 재활용용
    for (int i = 0; i < n; i++) // 입력
    {
        for (int j = 0; j < n; j++)
        {
            // cout<<map[i][j]<<" ";
            if(map[i][j]<0)
            {
                bfs(i,j,-map[i][j]);
            }
        }
        // cout<<endl;
    }
    cout << land;
    return 0;
}