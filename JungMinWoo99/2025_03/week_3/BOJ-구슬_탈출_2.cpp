#include <iostream>
#include <cstring>
using namespace std;

#define BLUE_OUT -1
#define RED_OUT 1
#define NOT_MOVED 2
#define MOVE_DONE 0

enum Dir
{
    Right,
    Up,
    Left,
    Down
};

class Marble
{
public:
    int x, y;
    Marble(int x, int y) : x(x), y(y) {}
};

class Board
{
public:
    Board(int n, int m) : n(n), m(m), R(0, 0), B(0, 0)
    {
        board = new char *[n];
        for (int i = 0; i < n; i++)
            board[i] = new char[m + 1];
        sboard = new char *[n];
        for (int i = 0; i < n; i++)
            sboard[i] = new char[m + 1];
    }

    void set_board()
    {
        for (int i = 0; i < n; i++)
        {
            cin >> board[i];
            strcpy(sboard[i], board[i]);
        }

        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < m; l++)
            {
                if (board[i][l] == 'R')
                    R = Marble(i, l);
                else if (board[i][l] == 'B')
                    B = Marble(i, l);
            }
        }
    }

    void show_board()
    {
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < m; l++)
                cout << board[i][l];
            cout << endl;
        }
    }

    char move_marbleR(Dir dir)
    {
        if (dir == Right)
        {
            if (board[R.x][R.y + 1] == '.')
            {
                board[R.x][R.y] = '.';
                board[R.x][++R.y] = 'R';
            }
            return board[R.x][R.y + 1];
        }
        else if (dir == Left)
        {
            if (board[R.x][R.y - 1] == '.')
            {
                board[R.x][R.y] = '.';
                board[R.x][--R.y] = 'R';
            }
            return board[R.x][R.y - 1];
        }
        else if (dir == Up)
        {
            if (board[R.x - 1][R.y] == '.')
            {
                board[R.x][R.y] = '.';
                board[--R.x][R.y] = 'R';
            }
            return board[R.x - 1][R.y];
        }
        else if (dir == Down)
        {
            if (board[R.x + 1][R.y] == '.')
            {
                board[R.x][R.y] = '.';
                board[++R.x][R.y] = 'R';
            }
            return board[R.x + 1][R.y];
        }
    }

    char checknext_marbleR(Dir dir)
    {
        if (dir == Right)
        {
            return board[R.x][R.y + 1];
        }
        else if (dir == Left)
        {
            return board[R.x][R.y - 1];
        }
        else if (dir == Up)
        {
            return board[R.x - 1][R.y];
        }
        else if (dir == Down)
        {
            return board[R.x + 1][R.y];
        }
    }

    char move_marbleB(Dir dir)
    {
        if (dir == Right)
        {
            if (board[B.x][B.y + 1] == '.')
            {
                board[B.x][B.y] = '.';
                board[B.x][++B.y] = 'B';
            }
            return board[B.x][B.y + 1];
        }
        else if (dir == Left)
        {
            if (board[B.x][B.y - 1] == '.')
            {
                board[B.x][B.y] = '.';
                board[B.x][--B.y] = 'B';
            }
            return board[B.x][B.y - 1];
        }
        else if (dir == Up)
        {
            if (board[B.x - 1][B.y] == '.')
            {
                board[B.x][B.y] = '.';
                board[--B.x][B.y] = 'B';
            }
            return board[B.x - 1][B.y];
        }
        else if (dir == Down)
        {
            if (board[B.x + 1][B.y] == '.')
            {
                board[B.x][B.y] = '.';
                board[++B.x][B.y] = 'B';
            }
            return board[B.x + 1][B.y];
        }
    }

    char checknext_marbleB(Dir dir)
    {
        if (dir == Right)
        {
            return board[B.x][B.y + 1];
        }
        else if (dir == Left)
        {
            return board[B.x][B.y - 1];
        }
        else if (dir == Up)
        {
            return board[B.x - 1][B.y];
        }
        else if (dir == Down)
        {
            return board[B.x + 1][B.y];
        }
    }

    int turn_board(Dir dir)
    {
        char r = checknext_marbleR(dir), b = checknext_marbleB(dir);
        int loop = 0;
        // cout << "move loop start" << endl;
        while (1)
        {
            if (r == '#' && b == '#')
            {
                if (loop == 0)
                    return NOT_MOVED; // 동작하지않음
                return MOVE_DONE;     // 동작완료
            }
            else if (r == 'B' && b == '#')
            {
                if (loop == 0)
                    return NOT_MOVED; // 동작하지않음
                return MOVE_DONE;     // 동작완료
            }
            else if (r == '#' && b == 'R')
            {
                if (loop == 0)
                    return NOT_MOVED; // 동작하지않음
                return MOVE_DONE;     // 동작완료
            }
            else if (b == 'O')
                return BLUE_OUT; // 파랑이 나감(실패)
            else if (r == 'O')
            {
                if (b == '#')
                    return RED_OUT; // 빨강만 나감(성공)
                else if (b == 'R')
                    return BLUE_OUT; // 파랑이 나감(실패)
            }
            r = move_marbleR(dir);
            b = move_marbleB(dir);
            // show_board();
            r = checknext_marbleR(dir);
            b = checknext_marbleB(dir);
            // cout << r << b << endl;
            loop++;
        }
        // cout << "move loop done" << endl;
    }

    int pathfinder(Dir dir) // dir: 이전에 움직인 방향
    {
        static int counter = 1;
        static int maxcounter = 11;
        if (counter + 1 == maxcounter)
            return maxcounter;
        if (counter == 0)
            counter = 1;
        char **bboard;
        bboard = new char *[n];
        for (int i = 0; i < n; i++)
            bboard[i] = new char[m + 1];
        backup_board(bboard);

        // cout << "loop start" << endl;
        // show_board();
        //  << counter << endl;
        for (int i = 1; i < 4; i += 2)
        {
            // show_board();
            // cout << "move strat" << Dir((int(dir) + i) % 4)<< endl;
            int turn_res = turn_board(Dir((int(dir) + i) % 4));

            // cout << "move done" <<tem<< endl;
            if (turn_res == BLUE_OUT)
            {
                // cout << "fail" << endl;
                load_board(bboard);
            }
            else if (turn_res == MOVE_DONE)
            {
                counter++;
                // cout << "recursion start" << endl;
                pathfinder(Dir((int(dir) + i) % 4));
                // cout << "recursion end" << endl;
                counter--;
                load_board(bboard);
            }
            else if (turn_res == NOT_MOVED)
            {
                // cout << "block" << endl;
                continue;
            }
            else if (turn_res == RED_OUT)
            {
                // show_board();
                // cout << "clear" << endl;
                maxcounter = ++counter;
                // cout << counter << endl;
                counter--;
                load_board(bboard);
                return maxcounter;
            }
            // cout << "one tick done" << endl;
            // cout << counter << endl;
        }
        // cout << "loop done" << endl;
        for (int i = 0; i < n; i++)
            delete[] bboard[i];
        delete[] bboard;
        return maxcounter;
    }

    int pathfinder()
    {
        char **bboard;
        int maxcounter = 11;
        bboard = new char *[n];
        for (int i = 0; i < n; i++)
            bboard[i] = new char[m + 1];
        backup_board(bboard);
        for (int i = 0; i < 4; i++)
        {
            int res = turn_board(Dir(i));
            if (res == MOVE_DONE)
            {
                maxcounter = pathfinder(Dir(i));
            }
            else if (res == RED_OUT)
            {
                return RED_OUT;
            }
            load_board(bboard);
        }
        return maxcounter;
    }

private:
    char **sboard;
    char **board;
    int n, m;
    Marble R, B;

    void backup_board(char **bboard)
    {
        for (int i = 0; i < n; i++)
        {
            strcpy(bboard[i], board[i]);
        }
    }

    void load_board(char **bboard)
    {
        for (int i = 0; i < n; i++)
        {
            strcpy(board[i], bboard[i]);
            for (int i = 0; i < n; i++)
            {
                for (int l = 0; l < m; l++)
                {
                    if (board[i][l] == 'R')
                        R = Marble(i, l);
                    else if (board[i][l] == 'B')
                        B = Marble(i, l);
                }
            }
        }
    }

    void reset_board()
    {
        for (int i = 0; i < n; i++)
        {
            strcpy(board[i], sboard[i]);
        }

        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < m; l++)
            {
                if (board[i][l] == 'R')
                    R = Marble(i, l);
                else if (board[i][l] == 'B')
                    B = Marble(i, l);
            }
        }
    }
};
int main(void)
{
    int n, m;
    int answer = -1;
    cin >> n >> m;
    Board main(n, m);
    main.set_board();
    answer = main.pathfinder();
    if (answer == 11)
        answer = -1;
    cout << answer;
    return 0;
}
