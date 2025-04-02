#include <iostream>
#include <queue>
using namespace std;

int N, K, L; // N : 보드 크기, K : 사과 개수, L : 방향 전환 횟수
int board[101][101]; // 0: 빈 칸, 1: 사과, 2: 뱀
int ydir[] = { -1, 0, 1, 0 };
int xdir[] = { 0, 1, 0, -1 };
int curDir = 1; // 처음 방향: 오른쪽
int curY = 1, curX = 1; // 뱀의 초기 위치
int cnt = 0; // 게임 진행 시간
queue<pair<int, int>> snake; // 뱀의 위치 (꼬리 -> 머리 순서)

struct Turn {
   int time;
   char direction;
};

queue<Turn> turns; // 방향 전환 정보

void GoStraightAnd() {
   while (true) {
      cnt++;

      int ny = curY + ydir[curDir];
      int nx = curX + xdir[curDir];

      // 벽 or 자기 자신과 부딪히면 종료
      if (ny < 1 || ny > N || nx < 1 || nx > N || board[ny][nx] == 2) {
         cout << cnt << "\n";
         return;
      }

      // 사과가 있는 경우
      if (board[ny][nx] == 1) {
         board[ny][nx] = 2;
         snake.push({ ny, nx });
      }

      // 사과가 없는 경우
      else {
         board[ny][nx] = 2;
         snake.push({ ny, nx });

         // 꼬리 제거
         int tailY = snake.front().first;
         int tailX = snake.front().second;
         snake.pop();
         board[tailY][tailX] = 0;
      }

      curY = ny;
      curX = nx;

      if (!turns.empty() && turns.front().time == cnt) {
         char c = turns.front().direction;
         turns.pop();
         if (c == 'D') {
            curDir = (curDir + 1) % 4; // 오른쪽 회전
         }
         else {
            curDir = (curDir + 3) % 4; // 왼쪽 회전
         }
      }
   }
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(NULL);

   cin >> N >> K;

   for (int i = 0; i < K; i++) {
      int y, x;
      cin >> y >> x;
      board[y][x] = 1;
   }

   cin >> L;
   for (int i = 0; i < L; i++) {
      int t;
      char dir;
      cin >> t >> dir;
      turns.push({ t, dir });
   }

   board[1][1] = 2;
   snake.push({ 1, 1 });

   GoStraightAnd();

   return 0;
}
