#include <iostream>
#define endl '\n'

#include <vector>
#include <algorithm>

using namespace std;

#define UNKOWN -1
#define FIRST_WIN 0
#define FIRST_LOSS 1

class GridGame
{
public:
    GridGame(int n, int m, int k) : N(n), M(m), K(k), grid(n, vector<char>(m)), DP(n, vector<char>(m, UNKOWN))
    {
        DP[N - 1][M - 1] = FIRST_LOSS;

        move_set.emplace_back(0, 1);
        move_set.emplace_back(1, 0);
        for (int dia = 1; dia <= K; dia++)
            move_set.emplace_back(dia, dia);
    }

    void InputGrid()
    {
        for (auto &row : grid)
            for (auto &ele : row)
                cin >> ele;
    }

    int FillDP(int n, int m)
    {
        if (DP[n][m] == UNKOWN)
        {
            int game_res = FIRST_WIN;
            for (auto p : move_set)
            {
                pair<int, int> next = {n + p.first, m + p.second};
                if (CheckBound(next.first, next.second))
                    game_res |= FillDP(next.first, next.second);
            }

            DP[n][m] = !game_res;
        }

        return DP[n][m];
    }

private:
    int N, M, K;
    vector<vector<char>> grid;
    vector<vector<char>> DP;
    vector<pair<int, int>> move_set;

    bool CheckBound(int r, int c)
    {
        return -1 < r && r < N && -1 < c && c < M && grid[r][c] == '.';
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    GridGame grid_game(N, M, K);
    grid_game.InputGrid();
    int test_case;
    cin >> test_case;
    for (int tc = 0; tc < test_case; tc++)
    {
        int r, c;
        cin >> r >> c;
        int game_res = grid_game.FillDP(r-1, c-1);

        if(game_res == FIRST_WIN)
            cout<<"First"<<endl;
        else
            cout<<"Second"<<endl;
    }

    return 0;
}