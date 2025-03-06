#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> board;

class FindAnswer {
   public:
    FindAnswer(vector<vector<int>>& input) : grid(input) {
        out_of_bound.assign(grid[0].size(), -1);
    }

    int getAnswer() {
        for (int i = 0; i < grid.size(); i++) {
            for (int l = 0; l < grid[0].size(); l++) {
                for (int type = 0; type < 19; type++) {
                    int part_val = getPartValue(i, l, type);
                    max = max > part_val ? max : part_val;
                }
            }
        }
        return max;
    }

   private:
    vector<vector<int>>& grid;
    vector<int> out_of_bound;
    int max = 0;

    int operator()(int r, int c) {
        if (!(-1 < r && r < grid.size() && -1 < c && c < grid[0].size()))
            return -3000;
        else
            return grid[r][c];
    }

    int getPartValue(int r, int c, int type) {
        switch (type) {
            case 0:
                return getPart1_1Value(r, c);
            case 1:
                return getPart1_2Value(r, c);
            case 2:
                return getPart2_1Value(r, c);
            case 3:
                return getPart3_1Value(r, c);
            case 4:
                return getPart3_2Value(r, c);
            case 5:
                return getPart3_3Value(r, c);
            case 6:
                return getPart3_4Value(r, c);
            case 7:
                return getPart3_5Value(r, c);
            case 8:
                return getPart3_6Value(r, c);
            case 9:
                return getPart3_7Value(r, c);
            case 10:
                return getPart3_8Value(r, c);
            case 11:
                return getPart4_1Value(r, c);
            case 12:
                return getPart4_2Value(r, c);
            case 13:
                return getPart4_3Value(r, c);
            case 14:
                return getPart4_4Value(r, c);
            case 15:
                return getPart5_1Value(r, c);
            case 16:
                return getPart5_2Value(r, c);
            case 17:
                return getPart5_3Value(r, c);
            case 18:
                return getPart5_4Value(r, c);
            default:
                return -1;
        }
    }

    int getPart1_1Value(int r, int c) {
        return (*this)(r, c) + (*this)(r, c + 1) + (*this)(r, c + 2) + (*this)(r, c + 3);
    }

    int getPart1_2Value(int r, int c) {
        return (*this)(r, c) + (*this)(r + 1, c) + (*this)(r + 2, c) + (*this)(r + 3, c);
    }

    int getPart2_1Value(int r, int c) {
        return (*this)(r, c) + (*this)(r + 1, c) + (*this)(r, c + 1) + (*this)(r + 1, c + 1);
    }

    int getPart3_1Value(int r, int c) {
        return (*this)(r, c) + (*this)(r + 1, c) + (*this)(r + 2, c) + (*this)(r + 2, c + 1);
    }

    int getPart3_2Value(int r, int c) {
        return (*this)(r, c) + (*this)(r + 1, c) + (*this)(r + 2, c) + (*this)(r, c + 1);
    }

    int getPart3_3Value(int r, int c) {
        return (*this)(r, c + 1) + (*this)(r + 1, c + 1) + (*this)(r + 2, c + 1) + (*this)(r, c);
    }

    int getPart3_4Value(int r, int c) {
        return (*this)(r, c + 1) + (*this)(r + 1, c + 1) + (*this)(r + 2, c + 1) + (*this)(r + 2, c);
    }

    int getPart3_5Value(int r, int c) {
        return (*this)(r, c) + (*this)(r, c + 1) + (*this)(r, c + 2) + (*this)(r + 1, c);
    }

    int getPart3_6Value(int r, int c) {
        return (*this)(r, c) + (*this)(r, c + 1) + (*this)(r, c + 2) + (*this)(r + 1, c + 2);
    }

    int getPart3_7Value(int r, int c) {
        return (*this)(r + 1, c) + (*this)(r + 1, c + 1) + (*this)(r + 1, c + 2) + (*this)(r, c);
    }

    int getPart3_8Value(int r, int c) {
        return (*this)(r + 1, c) + (*this)(r + 1, c + 1) + (*this)(r + 1, c + 2) + (*this)(r, c + 2);
    }

    int getPart4_1Value(int r, int c) {
        return (*this)(r, c) + (*this)(r + 1, c) + (*this)(r + 2, c) + (*this)(r + 1, c + 1);
    }

    int getPart4_2Value(int r, int c) {
        return (*this)(r, c + 1) + (*this)(r + 1, c + 1) + (*this)(r + 2, c + 1) + (*this)(r + 1, c);
    }

    int getPart4_3Value(int r, int c) {
        return (*this)(r, c) + (*this)(r, c + 1) + (*this)(r, c + 2) + (*this)(r + 1, c + 1);
    }

    int getPart4_4Value(int r, int c) {
        return (*this)(r + 1, c) + (*this)(r + 1, c + 1) + (*this)(r + 1, c + 2) + (*this)(r, c + 1);
    }

    int getPart5_1Value(int r, int c) {
        return (*this)(r, c) + (*this)(r + 1, c) + (*this)(r + 1, c + 1) + (*this)(r + 2, c + 1);
    }

    int getPart5_2Value(int r, int c) {
        return (*this)(r, c + 1) + (*this)(r + 1, c) + (*this)(r + 1, c + 1) + (*this)(r + 2, c);
    }

    int getPart5_3Value(int r, int c) {
        return (*this)(r, c) + (*this)(r, c + 1) + (*this)(r + 1, c + 1) + (*this)(r + 1, c + 2);
    }

    int getPart5_4Value(int r, int c) {
        return (*this)(r + 1, c) + (*this)(r + 1, c + 1) + (*this)(r, c + 1) + (*this)(r, c + 2);
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    board.resize(N);
    for (int i = 0; i < N; i++) {
        board[i].resize(M);
        for (int l = 0; l < M; l++)
            cin >> board[i][l];
    }

    FindAnswer main(board);

    cout << main.getAnswer();

    return 0;
}