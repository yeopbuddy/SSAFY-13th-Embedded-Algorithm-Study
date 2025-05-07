#include <iostream>
#include <vector>
using namespace std;

// 빈칸들에 대해 숫자 1~9를 모두 시도해보되
// 해당 행/열/박스에 이미 존재하면 skip
// 조건 만족하면 값을 채운 뒤 다음 빈칸으로 이동 (solve(idx+1))
// 이후 진행에서 실패했다면 backtracking

int board[9][9];
bool row[9][10];      // row[i][n] = i행에 n이 있는가
bool col[9][10];      // col[j][n] = j열에 n이 있는가
bool box[9][10];      // box[b][n] = b번 박스에 n이 있는가

vector<pair<int, int>> blanks; // 0이 들어간 위치 저장

int getBoxIndex(int x, int y) { 
    int section;
    if (0 <= x && x < 3) // section 1, 2, 3
        section = 1;
    else if (3 <= x && x < 6) // section 4, 5, 6
        section = 4;
    else // section 7, 8, 9
        section = 7;
    if (3 <= y && y < 6) // section calculate
        section++;
    else if (6 <= y && y < 9) // section calculate
        section += 2;
    return section; // 1 2 3 , 4 5 6 , 7 8 9
}

bool solve(int idx) {
    if (idx == blanks.size()) {
        return true; // 모든 칸 채움
    }

    int x = blanks[idx].first;
    int y = blanks[idx].second;
    int b = getBoxIndex(x, y) - 1;

    for (int num = 1; num <= 9; num++) {
        if (!row[x][num] && !col[y][num] && !box[b][num]) {
            // 가능하면 시도
            board[x][y] = num;
            row[x][num] = col[y][num] = box[b][num] = true;

            if (solve(idx + 1)) return true; // 다음 칸

            // 백트래킹
            board[x][y] = 0;
            row[x][num] = col[y][num] = box[b][num] = false;
        }
    }
    return false; // 현재 경로로는 해결 불가
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
            if (board[i][j] == 0) {
                blanks.push_back({i, j});
            } else {
                int num = board[i][j];
                row[i][num] = col[j][num] = box[getBoxIndex(i, j) - 1][num] = true;
            }
        }
    }

    solve(0);

    // 출력
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
