#include <iostream>
#include <string>

#include <queue>

using namespace std;

class Board
{
public:
    Board(int n) : n(n), board(n, vector<int>(n, 0))
    {
    }

    void set_board()
    {
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < n; l++)
            {
                cin >> board[i][l];
            }
        }
    }

    void backup_board(vector<vector<int>> &bboard)
    {
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < n; l++)
            {
                bboard[i][l] = board[i][l];
            }
        }
    }

    void load_board(vector<vector<int>> &bboard)
    {
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < n; l++)
            {
                board[i][l] = bboard[i][l];
            }
        }
    }

    void show_board()
    {
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < n; l++)
            {
                cout << board[i][l] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    void slide_line(vector<int> &arr, int dir)
    { // 1 is right push, 0 is left push
        queue<int> slide;
        queue<int> slide_res;
        if (dir == 0)
        {
            for (int i = 0; i < n; i++)
            {
                if (arr[i] != 0)
                {
                    slide.push(arr[i]);
                    arr[i] = 0;
                }
            }
            while (!slide.empty())
            {
                int tem = slide.front();
                slide.pop();
                if (!slide.empty() &&tem == slide.front())
                {
                    slide.pop();
                    slide_res.push(tem * 2);
                }
                else
                {
                    slide_res.push(tem);
                }
            }
            for (int i = 0; i < n && !slide_res.empty(); i++)
            {
                int tem = slide_res.front();
                slide_res.pop();
                arr[i] = tem;
            }
        }
        else
        {
            for (int i = n-1; i > -1; i--)
            {
                if (arr[i] != 0)
                {
                    slide.push(arr[i]);
                    arr[i] = 0;
                }
            }
            while (!slide.empty())
            {
                int tem = slide.front();
                slide.pop();
                if (!slide.empty() &&tem == slide.front())
                {
                    slide.pop();
                    slide_res.push(tem * 2);
                }
                else
                {
                    slide_res.push(tem);
                }
            }
            for (int i = n-1; i > -1 && !slide_res.empty(); i--)
            {
                int tem = slide_res.front();
                slide_res.pop();
                arr[i] = tem;
            }
        }
    }

    void push_board(int dir)
    {
        if (dir == 1 || dir == 0)
        { // 1우 0좌
            for (int row = 0; row < n; row++)
            {
                slide_line(board[row], dir);
            }
        }
        else if (dir == 3 || dir == 2)
        { // 3아래 2위
            for (int col = 0; col < n; col++)
            {
                vector<int> col_slide; // 인덱스 0이 맨 앞에 저장됨
                for (int row = 0; row < n; row++)
                    col_slide.push_back(board[row][col]);
                slide_line(col_slide, dir - 2);
                for (int row = 0; row < n; row++)
                {
                    board[row][col] = col_slide[row];
                }
            }
        }
        return;
    }

    int find_max()
    {
        int max = 0;
        for (int i = 0; i < n; i++)
        {
            for (int l = 0; l < n; l++)
            {
                if (max < board[i][l])
                    max = board[i][l];
            }
        }
        return max;
    }

    int find_answer(int recur_depth = 0)
    {
        static int max = 0; // 최대값 저장

        vector<vector<int>> bboard(n, vector<int>(n, 0));
        backup_board(bboard);

        if (recur_depth == 5)
        {
            int tem = find_max();
            if (max < tem)
                max = tem;
            return max;
        }

        for (int i = 0; i < 4; i++)
        {
            push_board(i);
            find_answer(recur_depth + 1);
            load_board(bboard);
        }

        return max;
    }

private:
    vector<vector<int>> board;
    int n; // 행,열 수
};

int main(void)
{
    int n;
    cin >> n;
    Board main(n);
    main.set_board();
    cout << main.find_answer();
    return 0;
}