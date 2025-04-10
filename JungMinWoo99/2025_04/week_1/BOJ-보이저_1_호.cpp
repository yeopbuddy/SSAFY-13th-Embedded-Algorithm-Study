#include <iostream>
#define endl '\n'

#include <algorithm>
#include <cctype>
#include <numeric>
#include <vector>

using namespace std;

enum Dir
{
    None,
    Up,
    Right,
    Down,
    Left
};

int dy[] = {0,-1, 0, 1, 0};
int dx[] = {0,0, 1, 0, -1};

class Voyager
{
   public:
    Voyager(int N, int M) : row(N), col(M), board(N, vector<char>(M))
    {
        for (auto& row : board)
            for (auto& ele : row) cin >> ele;
    }

    void PrintAnswer()
    {
        int PR, PC;
        cin >> PR >> PC;

        PR--;
        PC--;
        int answer_val = 0;
        int answer_dir = 0;
        for (int dir = 1; dir <= 4; dir++)
        {
            Dir start_dir = (Dir)dir;
            int y = PR, x = PC;
            int move_cnt = 0;
            while (move_cnt < row * col * 2)
            {
                if (!CheckBound(y, x) || board[y][x] == 'C')
                    break;
                else if (board[y][x] == '/' || board[y][x] == '\\')
                    start_dir = Bounce(board[y][x], start_dir);

                y += dy[start_dir];
                x += dx[start_dir];

                move_cnt++;
            }
            
            if (answer_val < move_cnt)
            {
                answer_dir = dir;
                answer_val = move_cnt;
            }
        }

        if (answer_dir == Up) cout << 'U' << endl;

        if (answer_dir == Right) cout << 'R' << endl;

        if (answer_dir == Left) cout << 'L' << endl;

        if (answer_dir == Down) cout << 'D' << endl;

        if(answer_val < row * col * 2)
            cout<<answer_val<<endl;
        else
            cout<<"Voyager"<<endl;
    }

   private:
    int row, col;
    vector<vector<char>> board;

    Dir Bounce(char star, Dir d)
    {
        if (star == '/')
        {
            if (d == Right) return Up;
            if (d == Up) return Right;
            if (d == Left) return Down;
            if (d == Down) return Left;
        }

        if (star == '\\')
        {
            if (d == Right) return Down;
            if (d == Down) return Right;
            if (d == Left) return Up;
            if (d == Up) return Left;
        }
    }

    bool CheckBound(int r, int c)
    {
        return -1 < r && r < row && -1 < c && c < col;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N,M;
    cin>>N>>M;

    Voyager voyager(N,M);
    voyager.PrintAnswer();

    return 0;
}