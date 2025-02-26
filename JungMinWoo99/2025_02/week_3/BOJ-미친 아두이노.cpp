#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
#define endl '\n'

#include <cmath>
#include <deque>

using namespace std;
using IntP = pair<int, int>;

int dy[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
int dx[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

class Robots {
   public:
    Robots(int r, int c) :turn(0), R(r), C(c),is_end(false) {
        for (int i = 0; i < R; i++) {
            for (int l = 0; l < C; l++) {
                char input;
                cin >> input;
                if (input == 'I')
                    joensu = make_pair(i, l);
                else if (input == 'R')
                    crazy_robots.push_back(make_pair(i, l));
            }
        }
    }

    /*
    프로그램의 전체 흐름
    커맨드 입력 -> 종수 로봇 이동 -> 미친 로봇 이동 -> 로봇들의 충돌 판정 및 파괴 검사
    */
    void inputCommand(int dir) {
        if (!is_end) {
            moveJoensu(dir);
            moveCrazyRobots();
            renderBoard();
            turn++;
        }
    }

    void printBoard() {
        for (int i = 0; i < R; i++) {
            for (int l = 0; l < C; l++) {
                if (joensu.first == i && joensu.second == l)
                    cout << 'I';
                else if (board[i][l] == 1)
                    cout << 'R';
                else
                    cout << '.';
            }
            cout << endl;
        }
    }

    bool isGameEnd() {
        return is_end;
    }

	int getTurn()
	{
		return turn;
	}

   private:
    int R, C;
    IntP joensu;
    int turn;
    bool is_end;
    vector<vector<int>> board;//각각의 칸에 존재하는 로봇의 수를 기록
    deque<IntP> crazy_robots;

    void moveJoensu(int dir) {
        joensu = make_pair(joensu.first + dy[dir], joensu.second + dx[dir]);
    }

    //지정한 하나의 미친 로봇을 움직이는 함수
    IntP moveCrazy(IntP crazy) {
        int next_move_y = (joensu.first - crazy.first);
        if(next_move_y != 0)
			next_move_y /= abs(next_move_y);
		int next_move_x = (joensu.second - crazy.second);
		if(next_move_x != 0)
			next_move_x /= abs(next_move_x);
		return make_pair(crazy.first + next_move_y, crazy.second + next_move_x);
    }

    //모든 미친 로봇을 움직이는 함수
    void moveCrazyRobots() {
        int bot_cnt = crazy_robots.size();
        for (int i = 0; i < bot_cnt; i++) {
            auto crazy = crazy_robots.front();
            crazy_robots.pop_front();
            crazy_robots.push_back(moveCrazy(crazy));
        }
    }

    //모든 로봇이 움직인 이후 충돌 검사 및 로봇 파괴 판정 진행
    void renderBoard() {
        board.assign(R, vector<int>(C, 0));
        while (!crazy_robots.empty()) {
            auto crazy = crazy_robots.front();
			crazy_robots.pop_front();
            int cy = crazy.first;
            int cx = crazy.second;
            if (isEnd(crazy)) {
                is_end = true;
                return;
            }
            board[cy][cx]++;
        }
        for (int i = 0; i < R; i++) {
            for (int l = 0; l < C; l++) {
                if (board[i][l] > 1)
                    board[i][l] = 0;
                else if (board[i][l] == 1)
                    crazy_robots.push_back(make_pair(i, l));
            }
        }
    }

    //미친 로봇과 종수 로봇의 충돌 여부를 판단
    bool isEnd(IntP crazy) {
        return crazy.first == joensu.first && crazy.second == joensu.second;
    }
};

int main(void) {
    fastio;
    int R, C;
    cin >> R >> C;
    Robots bot(R, C);
    string command;
    cin >> command;
    for (char c : command) {
        bot.inputCommand(c - '1');
    }
    if (bot.isGameEnd())
        cout << "kraj " << bot.getTurn() << endl;
    else
        bot.printBoard();

    return 0;
}