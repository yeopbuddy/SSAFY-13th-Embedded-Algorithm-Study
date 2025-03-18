#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef pair<int, int> point;
typedef pair<int, char> moving;

int N, K, L;
int answer;

const vector<int> dy = {-1, 0, 1, 0};
const vector<int> dx = {0, 1, 0, -1};

vector<point> apple;
deque<moving> rotate_info;

class GameBoard
{
private:
    int grid_size;

public:
    GameBoard(int size) : grid_size(size)
    {
    }

    bool isOutOfBound(point pos)
    {
        if (!(1 <= pos.first && pos.first <= grid_size))
            return true;
        if (!(1 <= pos.second && pos.second <= grid_size))
            return true;
        return false;
    }

    bool isApple(point pos)
    {
        for (int i = 0; i < apple.size(); i++)
        {
            if (apple[i].first == pos.first && apple[i].second == pos.second)
                return true;
        }
        return false;
    }
};

class Snake
{
public:
    Snake(GameBoard &_board) : board(_board)
    {
        body.push_back(make_pair(1, 1));
        cur_dir = 1;
    }

    void TurnBody(char turn_dir)
    {
        if (turn_dir == 'D')
            cur_dir = (cur_dir + 1) % dy.size();
        else if (turn_dir == 'L')
            cur_dir = (cur_dir + 3) % dy.size();
    }

    bool isBody(point pos)
    {
        for (auto it = body.begin(); it != body.end(); it++)
        {
            if ((*it).first == pos.first && (*it).second == pos.second)
                return true;
        }
        return false;
    }

    bool isDie()
    {
        return die;
    }

    void Move()
    {
        point body_front = make_pair(body.front().first + dy[cur_dir], body.front().second + dx[cur_dir]);

        if (isBody(body_front) || board.isOutOfBound(body_front))
            die = true;
        else if (board.isApple(body_front))
        {
            body.push_front(body_front);
            EatApple(body_front);
        }
        else
        {
            body.pop_back();
            body.push_front(body_front);
        }
    }

    void EatApple(point pos)
    {
        for (int i = 0; i < apple.size(); i++)
        {
            if (apple[i].first == pos.first && apple[i].second == pos.second)
            {
                apple.erase(apple.begin() + i);
                return;
            }
        }
        return;
    }

private:
    GameBoard &board;
    deque<point> body;
    int cur_dir;
    bool die = false;
};

class Game
{
public:
    Game(GameBoard &_board, Snake &_snake) : board(_board), snake(_snake)
    {
        time = 0;
    }

    int getTime()
    {
        return time;
    }

    void StartGame()
    {
        while (!(snake.isDie()))
        {
            NextTick();
        }
    }

private:
    GameBoard &board;
    Snake &snake;
    int time;

    void NextTick()
    {
        time++;
        snake.Move();
        if (time == rotate_info.front().first)
        {
            snake.TurnBody(rotate_info.front().second);
            rotate_info.pop_front();
        }
    }
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    cin >> K;
    for (int i = 0; i < K; i++)
    {
        int n, m;
        cin >> n >> m;
        apple.push_back(make_pair(n, m));
    }
    cin >> L;
    for (int i = 0; i < L; i++)
    {
        int n;
        char m;
        cin >> n >> m;
        rotate_info.push_back(make_pair(n, m));
    }

    GameBoard board(N);
    Snake snake(board);
    Game game(board, snake);
    game.StartGame();
    answer = game.getTime();
    cout << answer << endl;
    return 0;
}