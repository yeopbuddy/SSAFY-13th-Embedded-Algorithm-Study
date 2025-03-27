// 7682번 틱택토
// 구현
/*
접근 방법:

*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

bool find_threes(const vector<vector<char>>& mat, char ch) {
    // 행과 열 확인
    for (int i = 0; i < 3; i++) {
        if (mat[i][0] == ch && mat[i][1] == ch && mat[i][2] == ch)
            return true;
        if (mat[0][i] == ch && mat[1][i] == ch && mat[2][i] == ch)
            return true;
    }
    // 대각선 확인
    if (mat[0][0] == ch && mat[1][1] == ch && mat[2][2] == ch)
        return true;
    if (mat[0][2] == ch && mat[1][1] == ch && mat[2][0] == ch)
        return true;
    return false;
}

bool determine_last_situation(const string &s) {
    int dotCount = 0, xCount = 0, oCount = 0;
    for (char c : s) {
        if (c == '.') dotCount++;
        if (c == 'X') xCount++;
        if (c == 'O') oCount++;
    }
    if (dotCount > 4)
        return false;

    // 3x3 판을 채우기
    vector<vector<char>> mat(3, vector<char>(3));
    for (int i = 0; i < 9; i++) {
        mat[i / 3][i % 3] = s[i];
    }

    if (dotCount == 0) {  // 판이 다 차있는 경우
        if (oCount == 4 && xCount == 5) {
            bool first_win = find_threes(mat, 'X');
            bool second_win = find_threes(mat, 'O');
            if ((first_win && second_win) || (!first_win && second_win))
                return false;
            else
                return true;
        } else {
            return false;
        }
    } else { // 빈 칸이 있는 경우, 승리 상태여야 함.
        if (oCount == xCount) {
            bool first_win = find_threes(mat, 'X');
            bool second_win = find_threes(mat, 'O');
            if (!first_win && second_win)
                return true;
            else
                return false;
        } else if (oCount + 1 == xCount) {
            bool first_win = find_threes(mat, 'X');
            bool second_win = find_threes(mat, 'O');
            if (first_win && !second_win)
                return true;
            else
                return false;
        } else {
            return false;
        }
    }
}

int main(void){
    fastio;
    string s;
    while (cin >> s) {
        if (s == "end")
            break;
        cout << (determine_last_situation(s) ? "valid" : "invalid") << endl;
    }
    return 0;
}
