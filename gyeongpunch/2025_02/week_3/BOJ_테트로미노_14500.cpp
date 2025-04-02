#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// 이런이런 노가다가 따로 없네요. dfs + T자 블록 따로 처리를 하려해도 이게 더 빠를 것 같아서 이렇게 풀었습니다.
// (0, 0)은 무조건 포함하고 모든 블록의 상대 위치를 저장했습니다. 대칭, 회전 처리에서 실수만 하지 않으면 쉽게 풀리는 것 같습니다.
// 윽 이런 문제 넘 시러요.

struct Point{
    int x, y;
};

const int MAX_SIZE = 500;

int N, M;
int arr[MAX_SIZE][MAX_SIZE];
int max_sum = 0;
Point total[19][3] = {
    {{0, 1}, {0, 2}, {0, 3}}, {{1, 0}, {2, 0}, {3, 0}}, // 작대기
    {{1, 0}, {0, 1}, {1, 1}}, // 네모
    {{0, 1}, {0, 2}, {1, 1}}, {{1, 0}, {1, 1}, {2, 0}}, {{1, 0}, {1, -1}, {1, 1}}, {{1, 0}, {2, 0}, {1, -1}}, // T자 블록
    {{1, 0}, {1, 1}, {2, 1}}, {{0, 1}, {1, 0}, {1, -1}}, {{1, 0}, {1, -1}, {2, -1}}, {{0, 1}, {1, 1}, {1, 2}}, // 지그재그
    {{1, 0}, {2, 0}, {2, 1}}, {{1, 0}, {1, -1}, {1, -2}}, {{0, 1}, {1, 1}, {2, 1}}, {{1, 0}, {0, 1}, {0, 2}}, // L자
    {{1, 0}, {2, 0}, {2, -1}}, {{0, 1}, {0, 2}, {1, 2}}, {{0, 1}, {1, 0}, {2, 0}}, {{1, 0}, {1, 1}, {1, 2}} // L자 대칭
};

bool bound_check(int x, int y){
    return 0<=x && x<N && 0<=y && y<M;
}

void get_calc(int x, int y){
    int sm, nx, ny;

    for(int i=0; i<19; i++){
        sm = arr[x][y];
        for(Point p : total[i]){
            nx = x + p.x;
            ny = y + p.y;
            if(bound_check(nx, ny)){
                sm += arr[nx][ny];
            }
            else {
                sm = 0;
                break;
            }
        }
        max_sum = max(max_sum, sm);
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

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            get_calc(i, j);
        }
    }

    cout << max_sum << '\n';

    return 0;
}