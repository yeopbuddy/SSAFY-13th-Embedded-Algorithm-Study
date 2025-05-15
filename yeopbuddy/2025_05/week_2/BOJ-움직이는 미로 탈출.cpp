// 1. 벽 옮기기 전 이동 가능한 좌표 모두 찾기
// 2. 벽 옮김. 이때 1에서 유효한 좌표 찾기 (벽은 아래로 내려오므로 1, 2는 묶어서 처리 가능할듯 .. 근데 걍 생각나는대로 함)
// 3. 만약 벽이 남아 있지 않고, 1-2를 통해 찾은 (이동 가능)좌표가 있을 경우 return 1
// 4. 만약 벽이 남아 있는데 1-2를 통해 찾은 (이동 가능)좌표가 없을 경우, return 0
// 5. 만약 벽이 남아 있는데 1-2를 통해 찾은 (이동 가능)좌표가 있을 경우, 다시 반복(1 -> 2 -> ..) 

// 8 x 8 배열이고, 벽은 아래로 내려온다 = 배열에서 벽이 전부 사라질 때 까지 생존 가능 여부 판단 문제
// 욱제는 이동할 수 있는 8개 방향 + 제자리 유지까지 9가지의 행동 이후의 좌표를 저장한다.
// 이때, 벽으로 막혀 있는 경우는 저장하지 않는다.
// 벽을 아래로 옮기고, 이때 벽에 갇힌 경우(벽과 같은 좌표인 경우)를 제외하고 새로 저장한다.
// 배열에서 벽이 전부 사라지기 전까지 반복한다.
// 이동한 점들에 대해 방문처리는 하지 않음

#include <iostream>
#include <vector>
using namespace std;
int answer = 1;
char ChessMap[8][8];
vector<pair<int, int>> paths;

int dx[9] = { -1, 1, 0, 0, -1, 1, -1, 1, 0 };
int dy[9] = { 0, 0, -1, 1, -1, -1, 1, 1, 0 }; // 상, 하, 좌, 우, 좌상, 좌하, 우상, 우하, 제자리

bool CheckWall() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (ChessMap[i][j] == '#') {
                return true;
            }
        }
    }
    return false;
}

void sweep() {
    for (int i = 6; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            ChessMap[i + 1][j] = ChessMap[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        ChessMap[0][i] = '.';
    }
}

void FindPath() {
    // sweep 전 갈 수 있는 path 모두 찾기
    vector<pair<int, int>> Newpaths;
    for (pair<int, int> p : paths) {
        int px = p.first;
        int py = p.second;
        for (int i = 0; i < 9; i++) {
            int nx = px + dx[i];
            int ny = py + dy[i];
            if ((0 <= nx && nx < 8) && (0 <= ny && ny < 8) && ChessMap[nx][ny] == '.') {
                Newpaths.push_back({ nx, ny });
            }
        }
    }
    // sweep 후 checkwall = false면 answer 1로 만들고 return
    sweep();
    if (!CheckWall() && !Newpaths.empty()) {
        return;
    }
    // checkwall = true면 path 중 가능한 path 빼고 나머지 삭제
    paths.clear();
    for (pair<int, int> p : Newpaths) {
        int px = p.first;
        int py = p.second;
        if (ChessMap[px][py] == '.') {
            paths.push_back({ px, py });
        }
    }
    if (paths.empty()) {
        answer = 0;
        return;
    }
    Newpaths.clear();
}


int main() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> ChessMap[i][j];
        }
    }
    paths.push_back({ 7,0 });
    while (CheckWall()) {
        FindPath();
    }
    cout << answer;
    return 0;
}