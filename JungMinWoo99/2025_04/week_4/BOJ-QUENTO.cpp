#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define BOOL int
#define BOARD_SIZE 3
using namespace std;

class Quento
{
public:
    Quento(int N, int M) : N(N), M(M), board(BOARD_SIZE, vector<char>(BOARD_SIZE)), visited(BOARD_SIZE, vector<BOOL>(BOARD_SIZE,false))
    {
        for (auto &row : board)
            for (auto &ele : row)
                cin >> ele;
    }

    bool DFS(int depth = 0)
    {
        if(depth == 2*M-1)
        {
            if(calGameRes()==N)
                return true;
            else
                return false;
        }
        if (depth == 0)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                for (int x = 0; x < BOARD_SIZE; x++)
                {
                    if (isdigit(board[y][x]))
                    {
                        pushCell({y, x});
                        if(DFS(depth + 1))
                            return true;
                        popCell();
                    }
                }
            }
        }
        else
        {
            pair<int, int> cur_pos = swiped_pos_stack.back();
            for (int dir = 0; dir < dy.size(); dir++)
            {
                pair<int, int> next_pos({cur_pos.first + dy[dir], cur_pos.second + dx[dir]});
                if (boundCheck(next_pos))
                {
                    pushCell(next_pos);
                    if(DFS(depth + 1))
                        return true;
                    popCell();
                }
            }
        }

        return false;
    }

    void printAnswer()
    {
        for(auto& coord:swiped_pos_stack)
            cout<<coord.first<<' '<<coord.second<<endl;
    }

    void printRes()
    {
        for(char c:swiped_cells_stack)
            cout<<c;
        cout<<endl;
    }

private:
    int N, M;
    vector<vector<BOOL>> visited;
    vector<vector<char>> board;
    vector<char> swiped_cells_stack;
    vector<pair<int, int>> swiped_pos_stack;

    int calGameRes()
    {
        int res = 0;
        bool is_add = true;
        for (char cell : swiped_cells_stack)
        {
            switch (cell)
            {
            case '+':
                is_add = true;
                break;
            case '-':
                is_add = false;
                break;
            default:
                if (is_add)
                    res += int(cell - '0');
                else
                    res -= int(cell - '0');
                break;
            }
        }

        return res;
    }

    void pushCell(const pair<int, int> &coord)
    {
        visited[coord.first][coord.second] = true;
        swiped_cells_stack.push_back(board[coord.first][coord.second]);
        swiped_pos_stack.push_back(coord);
    }

    void popCell()
    {
        auto& coord=swiped_pos_stack.back();
        visited[coord.first][coord.second] = false;
        swiped_cells_stack.pop_back();
        swiped_pos_stack.pop_back();
    }

    vector<int> dy = {0, -1, 0, 1};
    vector<int> dx = {1, 0, -1, 0};
    bool boundCheck(const pair<int, int> &coord)
    {
        return -1 < coord.first && coord.first < BOARD_SIZE && -1 < coord.second && coord.second < BOARD_SIZE && !visited[coord.first][coord.second];
    }
};


int main(void)
{
    int N, M;
    cin >> N >> M;
    Quento quento(N, M);
    if(quento.DFS())
    {
        cout<<1<<endl;
        quento.printAnswer();
    }
    else
    {
        cout<<0<<endl;
    }
}