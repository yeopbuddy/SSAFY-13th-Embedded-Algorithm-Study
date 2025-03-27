/*
복잡한 분기문으로 해결

- 유효한 틱택토 상태의 조건
1. (X의 갯수 - 1) <= (O의 갯수) <= (X의 갯수)
2. 격자의 빈 칸이 있는 상태로 끝났다면 게임은 다음의 조건을 만족
    - 반드시 X만 1빙고 이거나 O만 1빙고
    - 다음 두 조건 중 하나를 만족
        a. X가 빙고이면 (X의 갯수 - 1) == (O의 갯수)
        b. O가 빙고이면 (X의 갯수) == (O의 갯수)
3. 격자의 빈칸이 없다면 게임은 다음의 조건을 만족
    - O가 빙고면 안됨
*/

#include <iostream>
#define endl '\n'

#include <vector>
#include <deque>
#include <string>

using namespace std;

#define BOARD_SIZE 3

class TicTecTok
{
public:
    TicTecTok(string input) : board(BOARD_SIZE, vector<char>(BOARD_SIZE))
    {
        auto str_it = input.begin();
        for (auto &row : board)
            for (auto &ele : row)
                ele = *str_it++;
    }

    bool isValidGame()
    {
        CountXAndO();
        CountBingo();

        //1. (X의 갯수 - 1) <= (O의 갯수) <= (X의 갯수)
        if(!(cnt_x - 1 <= cnt_o && cnt_o <= cnt_x))
            return false;

        int total = cnt_x + cnt_o;
        //2. 격자의 빈 칸이 있는 상태로 끝났다면 게임은 다음의 조건을 만족
        if(total < BOARD_SIZE * BOARD_SIZE)
        {
            //- 반드시 X만 1빙고 이거나 O만 1빙고
            if(!(bingo_x_cnt == 1 ^ bingo_o_cnt == 1))
                return false;

            if(bingo_x_cnt == 1)
            {
                //a. X가 빙고이면 (X의 갯수 - 1) == (O의 갯수)
                if (cnt_o != cnt_x - 1)
                    return false;
            }
            else if(bingo_o_cnt == 1)
            {
                //b. O가 빙고이면 (X의 갯수) == (O의 갯수)
                if (cnt_o != cnt_x)
                    return false;
            }
        }
        else
        {
            //3. 격자의 빈칸이 없다면 게임은 다음의 조건을 만족
            if(bingo_o_cnt > 0)
                return false;
        }
        return true;
    }

private:
    vector<vector<char>> board;
    int cnt_x;
    int cnt_o;
    int bingo_x_cnt;
    int bingo_o_cnt;

    void CountXAndO()
    {
        cnt_x = 0;
        cnt_o = 0;
        for (auto &row : board)
            for (auto ele : row)
            {
                if (ele == 'X')
                    cnt_x++;
                else if (ele == 'O')
                    cnt_o++;
            }
    }

    void CountBingo()
    {
        bingo_x_cnt = 0;
        bingo_o_cnt = 0;

        for (int row = 0; row < BOARD_SIZE; row++)
        {
            vector<char> line;
            for (int col = 0; col < BOARD_SIZE; col++)
                line.push_back(board[row][col]);
            char bingo_res = checkBingo(line);
            if (bingo_res == 'X')
                bingo_x_cnt++;
            else if (bingo_res == 'O')
                bingo_o_cnt++;
        }

        for (int col = 0; col < BOARD_SIZE; col++)
        {
            vector<char> line;
            for (int row = 0; row < BOARD_SIZE; row++)
                line.push_back(board[row][col]);
            char bingo_res = checkBingo(line);
            if (bingo_res == 'X')
                bingo_x_cnt++;
            else if (bingo_res == 'O')
                bingo_o_cnt++;
        }

        vector<int> dy = {1, 1};
        vector<int> dx = {1, -1};
        vector<pair<int, int>> starts = {{0, 0}, {0, BOARD_SIZE - 1}};
        for (int dia = 0; dia < dy.size(); dia++)
        {
            vector<char> line;
            for (int i = 0; i < BOARD_SIZE; i++)
                line.push_back(board[starts[dia].first + dy[dia] * i][starts[dia].second + dx[dia] *i]);
            char bingo_res = checkBingo(line);
            if (bingo_res == 'X')
                bingo_x_cnt++;
            else if (bingo_res == 'O')
                bingo_o_cnt++;
        }
    }

    char checkBingo(const vector<char> &line)
    {
        bool is_bingo = true;
        for (int idx = 1; idx < BOARD_SIZE; idx++)
            is_bingo &= line[idx - 1] == line[idx];

        if (is_bingo)
            return line[0];
        else
            return ' ';
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(true)
    {
        string input;
        cin >> input;

        if(input.compare("end") == 0)
            break;
        
        TicTecTok ttt(input);
        bool is_valid = ttt.isValidGame();
        if(is_valid)
            cout<<"valid"<<endl;
        else
            cout<<"invalid"<<endl;
    }

    return 0;
}