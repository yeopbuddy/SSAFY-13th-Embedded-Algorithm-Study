#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define fastio               \
    ios::sync_with_stdio(0); \
    cout.tie(0);             \
    cin.tie(0);
using namespace std;
#define endl '\n'
#define wall 7
/*
R공과 B공의 위치만 넘김
한 방향으로 기울었을시 두 공이 겹쳐진다면
기울기 전 그 방향으로부터 먼 값이 한칸 뒤로가도록 구현
ff방식처럼 탐색하며 만약 방법을 찾는다면 종료
*/
int n, m;
int xy[4][2] = {
    -1, 0,
    0, -1,
    1, 0,
    0, 1};
struct RB
{
    pair<int, int> Red;
    pair<int, int> Blue;
};
vector<vector<int>> map;
queue<RB> q;
int roll(pair<int, int> e, int st)
{
    int dx, dy;
    dx = e.first + xy[st][0];
    dy = e.second + xy[st][1];
    while (1)
    {
        if (map[dx][dy] == 1) // 골
        {
            return -1;
        }
        else if (map[dx][dy] == wall) // 벽일경우 그전
        {
            if (st % 2 == 1)
                return dy - xy[st][1];
            else
                return dx - xy[st][0];
        }
        dx += xy[st][0];
        dy += xy[st][1];
    }
    return -2; // 오류
    // RB둘다 이동 만약 구멍 만나면 r일경우 종료 b일경우 push x 동시도 고려
}
int bfs()
{
    int cont = 1;
    while (!q.empty() && cont <= 10)
    {
        int si = q.size();
        for (int w = 0; w < si; w++)
        {
            RB e = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int a, b;
                a = roll(e.Red, i);
                b = roll(e.Blue, i);
                // cout<<a<<" "<<b<<endl;
                
                if(b==-1)
                {
                    continue;
                }
                if(a==-1)
                {
                    return cont;
                }
                if (a == b) // 움직인 결과와 나머지 좌표가 같은경우(이동시 두 좌표가 같은경우)
                {
                    if ((i % 2) && (e.Blue.first == e.Red.first)) // 홀수(좌우)일 때 같은 행일 경우
                    {
                        i == 1 ? e.Red.second < e.Blue.second ? b++ : a++ : e.Red.second < e.Blue.second ? a--
                                                                                                         : b--;
                    }
                    if (!(i % 2) && (e.Blue.second == e.Red.second)) // 짝수(상하)일 때 같은 열일 경우
                    {
                        i == 0 ? e.Red.first < e.Blue.first ? b++ : a++ : e.Red.first < e.Blue.first ? a--                                                                                                 : b--;
                    }
                }
                i % 2 ? (q.push({{e.Red.first,a},{e.Blue.first,b}})) : (q.push({{a,e.Red.second},{b,e.Blue.second}}));
            }
        }
        cont++;
    }
    return -1;
}
int main()
{
    pair<int, int> Red;
    pair<int, int> Blue;
    fastio;
    cin >> n >> m;
    char x;
    map.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            if (x == '#')
            {
                map[i][j] = wall;
            }
            else if (x == 'R')
            {
                Red.first = i;
                Red.second = j;
            }
            else if (x == 'B')
            {
                Blue.first = i;
                Blue.second = j;
            }
            else if (x == 'O')
            {
                map[i][j] = 1;
            }
            
        }
    }
    q.push({Red, Blue});
    cout<<bfs();
    // map[e.Blue.first][e.Blue.second]=1;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << map[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
