#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);
using namespace std;

// 다리는 바다에 접한 영역에 설치할 수 있습니다. 따라서 get_beach로 바다에 접한 좌표를 모두 구해줍니다. 동시에 arr에 group number를 매겨줍니다.
// 바다에 접한 좌표들 중 다른 group number에 도달하는 길이들 중 가장 최소를 구해봅시다.
// 답은 잘 나오니 최적화를 해봅시다. 현재의 길이가 이미 min_result보다 크면 더 뻗어갈 이유가 없습니다.
// min_result가 1보다 작아질 수 없으니 1이되면 모든 함수를 종료합시다.
// 매 beach 좌표 bfs마다 visited배열을 초기화하는 방법이 다소 비효율적인 것 같습니다. 더 좋은 방법은 없을까요?

const int MAX_N = 100;

struct Point{
    int x, y;
};

int N;
int arr[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
vector<Point> beach;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int min_result = MAX_N * MAX_N;

bool bound_check(int x, int y){
    return 0<=x && x<N && 0<=y && y<N;
}

void get_beach(int x, int y){
    int nx, ny;
    for(int i=0; i<4; i++){
        nx = x + dx[i];
        ny = y + dy[i];
        if(bound_check(nx, ny) && arr[nx][ny] == 0){
            beach.push_back({x, y});
            return;
        }
    }
}

void grouping(int x, int y, int& group_num){
    queue<Point> q;
    q.push({x, y});
    visited[x][y] = 1;
    arr[x][y] = group_num;

    Point now;
    int nx, ny;
    while(!q.empty()){
        now = q.front(); q.pop();

        for(int i=0; i<4; i++){
            nx = now.x + dx[i];
            ny = now.y + dy[i];
            if(bound_check(nx, ny) && visited[nx][ny] == 0 && arr[nx][ny] == 1){
                q.push({nx, ny});
                arr[nx][ny] = group_num;
                visited[nx][ny] = 1;
            }
        }
    }
}

void bfs(Point p){
    memset(visited, 0, sizeof(visited));

    queue<Point> q;
    q.push(p);
    visited[p.x][p.y] = 1;

    Point now;
    int nx, ny;
    while(!q.empty()){
        now = q.front(); q.pop();

        if(visited[now.x][now.y] > min_result) continue;

        for(int i=0; i<4; i++){
            nx = now.x + dx[i];
            ny = now.y + dy[i];

            if(bound_check(nx, ny) && visited[nx][ny] == 0){
                if(arr[nx][ny] == 0){
                    visited[nx][ny] = visited[now.x][now.y] + 1;
                    q.push({nx, ny});
                }

                else if (arr[nx][ny] != arr[p.x][p.y]){
                    min_result = min(min_result, visited[now.x][now.y] - 1);
                    return;
                }
            }
        }

    }
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
        }
    }

    int nx, ny;
    int group_num = 0;
    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            if(arr[x][y] == 1){
                get_beach(x, y);

                if(visited[x][y] == 0){
                    grouping(x, y, ++group_num);
                }
            }
        }
    }

    for(Point p : beach){
        bfs(p);
        if(min_result == 1) break;
    }

    cout << min_result << '\n';

    return 0;
}