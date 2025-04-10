#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

/*
N*M
행성, 블랙홀, 빈 공간
행성만나면 전파방향 90도 / or \
시그널이 블랙홀 or 항성계 벗어날 때까지 전파
탐사선이 어느 방향으로 시그널을 보내면 항성계 내부에 있는 시간이 최대가 되는지

이거두 시키는대로 구현만 합시당
그런데 항성계 내에 갖히는 경우에는 break해줘야합니다. 그것이 뭐냐면 같은 칸에 같은 방향으로 다시 왔을 때입니다~~~~
이것만 처리해주면 쉽게 구현할 수 있습니다.
*/

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);
#define MAX_SZ 500

struct Point{
    int x, y, dir;
};

struct Info{
    int dir, time;
};

int N, M;
char arr[MAX_SZ][MAX_SZ];
int visited[4][MAX_SZ][MAX_SZ];
Point start;
Info maxInfo = {0, -1};
bool resultFlag = false;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
unordered_map<int, char> dirs = {
    {0, 'U'}, {1, 'R'}, {2, 'D'}, {3, 'L'}
};

bool bound_check(int x, int y){
    return 0<=x && x<N && 0<=y && y<M;
}

void simulation(){
    Point now = start;
    memset(visited, 0, sizeof(visited));
    Info nowInfo = {start.dir, 1};

    int nx, ny;
    while(true){
        if(visited[now.dir][now.x][now.y] == 1){
            maxInfo = nowInfo;
            resultFlag = true;
            return;
        }
        visited[now.dir][now.x][now.y] = 1;
        nx = now.x + dx[now.dir];
        ny = now.y + dy[now.dir];

        if(!bound_check(nx, ny)) break;
        if(arr[nx][ny] == 'C') break;

        now.x = nx;
        now.y = ny;
        nowInfo.time++;

        if(arr[nx][ny] == '/'){
            if(now.dir % 2 == 0){
                now.dir = (now.dir + 1) % 4;
            }
            else{
                now.dir = (now.dir + 3) % 4;
            }
        }
        else if(arr[nx][ny] == '\\'){
            if(now.dir % 2 == 0){
                now.dir = (now.dir + 3) % 4;
            }
            else{
                now.dir = (now.dir + 1) % 4;
            }
        }
    }

    if(maxInfo.time < nowInfo.time){
        maxInfo = nowInfo;
    }

}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
        }
    }
    
    int x, y;
    cin >> x >> y;
    start = {x-1, y-1};

    for(int i=0; i<4; i++){
        start.dir = i;
        simulation();

        if(resultFlag) break;
    }

    if(resultFlag){
        cout << dirs[maxInfo.dir] << '\n' << "Voyager" << '\n';
    }
    else{
        cout << dirs[maxInfo.dir] << '\n' << maxInfo.time << '\n';
    }

    return 0;
}