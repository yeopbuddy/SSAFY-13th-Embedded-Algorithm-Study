#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include <deque>
#include <tuple>

using namespace std;

vector<int> seq;
vector<vector<int>> totalseq;

map<int, vector<vector<int>>> VectorMap; // 번호 : 원본 보드
map<int, vector<vector<vector<int>>>> RotatedMap; // 번호 : [보드 번호][회전도수] = 회전된 보드

int ShortestPath = -1;

vector<vector<int>> RotateBoard(vector<vector<int>> Board, int rot) {
    vector<vector<int>> NewBoard(5, vector<int>(5));
    switch (rot) {
    case 0: NewBoard = Board; break; // 왼쪽 0도 회전
    case 1:
        for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) // 왼쪽 90도 회전
            NewBoard[i][j] = Board[4 - j][i];
        break;
    case 2:
        for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) // 왼쪽 180도 회전
            NewBoard[i][j] = Board[4 - i][4 - j];
        break;
    case 3:
        for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) // 왼쪽 270도 회전
            NewBoard[i][j] = Board[j][4 - i];
        break;
    }
    return NewBoard;
}

void PrecomputeRotations() {
    for (int i = 0; i < 5; i++) {
        vector<vector<vector<int>>> rotations(4);
        rotations[0] = VectorMap[i]; // 0도
        for (int r = 1; r < 4; r++) {
            rotations[r] = RotateBoard(rotations[r - 1], 1); // 회전 
        }
        RotatedMap[i] = rotations;
    }
}

void FindShortestPath(vector<int> BoardSeq, int a, int b, int c, int d, int e) {
    vector<vector<int>> BoardA = RotatedMap[BoardSeq[0]][a];
    vector<vector<int>> BoardB = RotatedMap[BoardSeq[1]][b];
    vector<vector<int>> BoardC = RotatedMap[BoardSeq[2]][c];
    vector<vector<int>> BoardD = RotatedMap[BoardSeq[3]][d];
    vector<vector<int>> BoardE = RotatedMap[BoardSeq[4]][e];

    if (BoardA[0][0] != 1 || BoardE[4][4] != 1) return; // 회전했는데 처음과 끝이 1 아니면 가지말아버려

    vector<vector<int>> TotalBoard; // 여기에 이어붙여서 2차원 vector로 3차원 탐방
    for (auto& SubVec : BoardA) TotalBoard.push_back(SubVec);
    for (auto& SubVec : BoardB) TotalBoard.push_back(SubVec);
    for (auto& SubVec : BoardC) TotalBoard.push_back(SubVec);
    for (auto& SubVec : BoardD) TotalBoard.push_back(SubVec);
    for (auto& SubVec : BoardE) TotalBoard.push_back(SubVec);

    bool visit[25][5];
    memset(visit, false, sizeof(visit));

    int dx[6] = { 0,0,1,-1,5, -5 };
    int dy[6] = { 1,-1,0,0,0, 0 }; // 상하좌우 + 위층, 아래층까지 총 6개의 가능한 움직임 고려

    deque<tuple<int, int, int>> dq;
    dq.push_back({ 0, 0, 0 }); // x, y, 거리
    visit[0][0] = true;

    while (!dq.empty()) {
        int px, py, pd;
        tie(px, py, pd) = dq.front();
        dq.pop_front();

        if (px == 24 && py == 4) {
            if (ShortestPath == -1 || ShortestPath > pd) {
                ShortestPath = pd; // 최단 경로 갱신
            }
            return;
        }

        if (ShortestPath != -1 && pd >= ShortestPath) continue; // 지금의 최단 경로 넘어설 경우 더이상 탐색 하지말아버려

        for (int i = 0; i < 6; i++) {
            int nx = px + dx[i];
            int ny = py + dy[i];
            if (0 <= nx && nx < 25 && 0 <= ny && ny < 5 && !visit[nx][ny] && TotalBoard[nx][ny] == 1) {
                
                int cz = px / 5, cx = px % 5; // current z
                int nz = nx / 5, nx_ = nx % 5; // next z
                if (abs(cz - nz) > 1) continue; // 이게 없으면 ... 층 간 탐색에 오류 발생 ..
                if (cz != nz && cx != nx_) continue; // 이동 후 층 수 다른데(층 간 이동 했는데) 로직 상 잘못 점프 뛴 경우도 패스
                

                visit[nx][ny] = true;
                dq.push_back({ nx, ny, pd + 1 });
            }
        }
    }
}

void MakeAll() {
    for (int i = 0; i < 5; i++) seq.push_back(i);
    do {
        totalseq.push_back(seq); // 보드 쌓는 순열 생성 : 출처 .. cppreference
    } while (next_permutation(seq.begin(), seq.end())); 
}

void CalculateAll() {
    for (int i = 0; i < 120; i++) {
        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 4; b++) {
                for (int c = 0; c < 4; c++) {
                    for (int d = 0; d < 4; d++) {
                        for (int e = 0; e < 4; e++) { // 6중 for문.. 이거 진짜에요?
                            FindShortestPath(totalseq[i], a, b, c, d, e);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        vector<vector<int>> BOARD(5, vector<int>(5));
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                cin >> BOARD[j][k];
            }
        }
        VectorMap[i] = BOARD;
    }

    PrecomputeRotations(); // 미리 회전해서 정보들 저장
    MakeAll();             // 순열 생성
    CalculateAll();        // 모든 경우의 수 중 최단 거리 탐색
    cout << ShortestPath;
}