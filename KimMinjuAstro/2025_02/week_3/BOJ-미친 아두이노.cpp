#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int R, C;
struct Coord
{
	int y;
	int x;
};
vector<Coord>crazyArduino;
Coord jongSu;
char board[101][101];
string moveStr;
int endFlag = 0;
int ydir[10] = { 0,1,1,1,0,0,0,-1,-1,-1 };
int xdir[10] = { 0,-1,0,1,-1,0,1,-1,0,1 };


// R 움직이는 함수
void MoveR(int targetY, int targetX) {

	for (int i = 0; i < crazyArduino.size(); i++) {
		int curArdY = crazyArduino[i].y;
		int curArdX = crazyArduino[i].x;
		if (curArdY == -1 || curArdX == -1) continue;
		board[curArdY][curArdX] = '.';
	}

	for (int i = 0; i < crazyArduino.size(); i++) {
		int curArdY = crazyArduino[i].y;
		int curArdX = crazyArduino[i].x;
		if (curArdY == -1 || curArdX == -1) continue;

		int dir = -1;

		// 방향벡터 정하기
		if (targetY > curArdY && targetX < curArdX)dir = 1;
		if (targetY > curArdY && targetX == curArdX)dir = 2;
		if (targetY > curArdY && targetX > curArdX)dir = 3;

		if (targetY == curArdY && targetX < curArdX)dir = 4;
		if (targetY == curArdY && targetX > curArdX)dir = 6;

		if (targetY < curArdY && targetX < curArdX)dir = 7;
		if (targetY < curArdY && targetX == curArdX)dir = 8;
		if (targetY < curArdY && targetX > curArdX)dir = 9;

		int newArdY = curArdY + ydir[dir];
		int newArdX = curArdX + xdir[dir];

		// 종수한테 도달하면 게임 긑
		if (newArdY == targetY && newArdX == targetX) {
			endFlag = 1;
			return;
		}
		crazyArduino[i].y = newArdY;
		crazyArduino[i].x = newArdX;
	}
	
	// 같은 좌표로 모인 R들 폭파
	int cnt[101][101] = { 0 };
	for (int i = 0; i < crazyArduino.size(); i++)
	{
		int curArdY = crazyArduino[i].y;
		int curArdX = crazyArduino[i].x;
		if (curArdY == -1 || curArdX == -1) continue;
		cnt[curArdY][curArdX]++;
	}
	for (int i = 0; i < crazyArduino.size(); i++) {
		int curArdY = crazyArduino[i].y;
		int curArdX = crazyArduino[i].x;
		if (curArdY == -1 || curArdX == -1) continue;

		if (cnt[curArdY][curArdX] > 1) {
			crazyArduino[i].y = -1;
			crazyArduino[i].x = -1;
		}
		else {
			board[curArdY][curArdX] = 'R';
		}
	}

}
int main() {
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 'I') {
				jongSu.y = i;
				jongSu.x = j;
			}
			if (board[i][j] == 'R') {
				crazyArduino.push_back({ i, j });
			}
		}
	}

	cin >> moveStr;
	for (int i = 0; i < moveStr.length(); i++)
	{
		int currentDir = moveStr[i] - '0';
		board[jongSu.y][jongSu.x] = '.';
		jongSu.y += ydir[currentDir];
		jongSu.x += xdir[currentDir];
		if (board[jongSu.y][jongSu.x] == 'R') {
			cout << "kraj " << i+1 << "\n";
			return 0;
		}
		board[jongSu.y][jongSu.x] = 'I';

		MoveR(jongSu.y, jongSu.x);
		if (endFlag == 1) {
			cout << "kraj " << i+1 << "\n";
			return 0;
		}
		if (i == moveStr.length() - 1) {
			//cout << i + 1 << "번째 움직임\n";
			for (int i = 0; i < R; i++)
			{
				for (int j = 0; j < C; j++)
				{
					cout << board[i][j];
				}cout << "\n";
			}cout << "\n";
		}
	}
}
