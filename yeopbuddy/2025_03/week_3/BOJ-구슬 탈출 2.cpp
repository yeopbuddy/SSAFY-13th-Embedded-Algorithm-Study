// 아 진짜 디버깅하느라 눈 빠지는 줄 알았다
// 구슬 상하좌우 움직임 구현은 4개의 함수를 통해, x, y 좌표를 받아 전역으로 선언된 MAP을 순회하며 이동하는 방식으로 구현
// BFS 함수에서 Deque을 이용해 pop된 두 구슬의 좌표를 받아 상하좌우 움직임을 수행 (참조를 통한 값 변경)
// 움직이기 이전 두 구슬의 x, y좌표를 비교해 좌/우 또는 상/하 겹치는 구슬의 경우는
// 가로가 겹치는 경우 어떤 구슬이 왼쪽에 있었는지, 세로가 겹치는 경우 어떤 구슬이 위에 있었는지 판단
// 움직인 후 두 구슬의 좌표가 겹치면 위 경우에 따라 한 구슬을 옮겨주는 식으로 구현 (ex. 왼쪽으로 기울여서 겹쳤는데 원래 왼쪽 구슬이 파랑일 경우 빨강을 오른쪽으로 한 칸 옮겨줌)
// 겹치는 탐색을 줄이기 위해 4차원 ㅋㅋ 방문 bool 배열 사용
// 어떤 공이라도 홀컵에 들어간 경우 움직이지 않게 하기 위해 상하좌우 움직임 함수에 첫 조건 추가
// 상하좌우 한방에 구현한 사람이 1등드셍

#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
using namespace std;
vector<vector<char>> MAP;
int X_SIZE, Y_SIZE;
int BX, BY, RX, RY, HX, HY;
bool visited[11][11][11][11]; // ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ

void MOVE_LEFT(int & x, int & y) {
	int MX = x; int MY = y;
	if ((MX != HX || MY != HY)) { // 홀컵에 들어간 경우 못 움직이게 하기 위한 조건
		while (true) {
			if (MY - 1 >= 0) {
				if (MAP[MX][MY - 1] == '.') {
					MY--;
				}
				else if (MAP[MX][MY - 1] == 'O') {
					MY--;
					break;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	x = MX; y = MY;
}

void MOVE_RIGHT(int& x, int& y) {
	int MX = x; int MY = y;
	if ((MX != HX || MY != HY)) { // 홀컵에 들어간 경우 못 움직이게 하기 위한 조건
		while (true) {
			if (MY + 1 < Y_SIZE) {
				if (MAP[MX][MY + 1] == '.') {
					MY++;
				}
				else if (MAP[MX][MY + 1] == 'O') {
					MY++;
					break;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	x = MX; y = MY;
}

void MOVE_UP(int& x, int& y) {
	int MX = x; int MY = y;
	if ((MX != HX || MY != HY)) { // 홀컵에 들어간 경우 못 움직이게 하기 위한 조건
		while (true) {
			if (MX - 1 >= 0) {
				if (MAP[MX - 1][MY] == '.') {
					MX--;
				}
				else if (MAP[MX - 1][MY] == 'O') {
					MX--;
					break;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	x = MX; y = MY;
}

void MOVE_DOWN(int& x, int& y) {
	int MX = x; int MY = y;
	if ((MX != HX || MY != HY)) { // 홀컵에 들어간 경우 못 움직이게 하기 위한 조건
		while (true) {
			if (MX + 1 < X_SIZE) {
				if (MAP[MX + 1][MY] == '.') {
					MX++;
				}
				else if (MAP[MX + 1][MY] == 'O') {
					MX++;
					break;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	x = MX; y = MY;
}

void BFS() {
	int trial = 0;
	deque <tuple<int, int, int, int, int>> dq;
	dq.push_back({ BX, BY, RX, RY, trial});
	visited[BX][BY][RX][RY] = true;
	bool failure = true; // 애초에 실패로 잡아두고, while문 내에서 false 처리가 안되면 fail
	while (!dq.empty()){
		int Pop_BlueX, Pop_BlueY, Pop_RedX, Pop_RedY, Pop_trial;
		tie(Pop_BlueX, Pop_BlueY, Pop_RedX, Pop_RedY, Pop_trial) = dq.front(); // ㅋㅋ 깔끔띠
		dq.pop_front();
		if (Pop_RedX == HX && Pop_RedY == HY && (Pop_BlueX != HX || Pop_BlueY != HY)) {
			failure = false;
			cout << Pop_trial;
			break;
		}
		// 파랑, 빨강 구슬의 상/하/좌/우 움직임 후 X, Y 좌표 저장하기 위한 2x4x2 = 16개의 변수
		int Left_MoveBlueX, Left_MoveBlueY, Left_MoveRedX, Left_MoveRedY, Right_MoveBlueX, Right_MoveBlueY, Right_MoveRedX, Right_MoveRedY;
		int Up_MoveBlueX, Up_MoveBlueY, Up_MoveRedX, Up_MoveRedY, Down_MoveBlueX, Down_MoveBlueY, Down_MoveRedX, Down_MoveRedY;

		//  콤마 연산자 이용, 한줄에 여러 대입
		Left_MoveBlueX = Right_MoveBlueX = Pop_BlueX, Left_MoveBlueY = Right_MoveBlueY = Pop_BlueY;
		Left_MoveRedX = Right_MoveRedX = Pop_RedX, Left_MoveRedY = Right_MoveRedY = Pop_RedY;
		Up_MoveBlueX = Down_MoveBlueX = Pop_BlueX, Up_MoveBlueY = Down_MoveBlueY = Pop_BlueY;
		Up_MoveRedX = Down_MoveRedX = Pop_RedX, Up_MoveRedY = Down_MoveRedY = Pop_RedY;

		MOVE_LEFT(Left_MoveBlueX, Left_MoveBlueY); MOVE_LEFT(Left_MoveRedX, Left_MoveRedY); // 왼쪽으로 기울이기
		MOVE_RIGHT(Right_MoveBlueX, Right_MoveBlueY); MOVE_RIGHT(Right_MoveRedX, Right_MoveRedY); // 오른쪽으로 기울이기
		MOVE_UP(Up_MoveBlueX, Up_MoveBlueY); MOVE_UP(Up_MoveRedX, Up_MoveRedY); // 위로 기울이기
		MOVE_DOWN(Down_MoveBlueX, Down_MoveBlueY); MOVE_DOWN(Down_MoveRedX, Down_MoveRedY); // 아래로 기울이기

		if (Pop_BlueX == Pop_RedX) { // 두 공의 행(가로)이 같을 경우 : 좌/우 판단후 세로 좌표 같으면 후처리
			bool BLUE_LEFT; // 좌/우 판단
			if (Pop_BlueY < Pop_RedY) { 
				BLUE_LEFT = true;
			}
			else{ 
				BLUE_LEFT = false;
			}
			// 후처리
			if (Left_MoveBlueY == Left_MoveRedY && (HX != Left_MoveBlueX || HY != Left_MoveBlueY)) {
				if (BLUE_LEFT) {
					Left_MoveRedY++;
				}
				else {
					Left_MoveBlueY++;
				}
			}
			if (Right_MoveBlueY == Right_MoveRedY && (HX != Right_MoveBlueX || HY != Right_MoveBlueY)) {
				if (BLUE_LEFT) {
					Right_MoveBlueY--;
				}
				else {
					Right_MoveRedY--;
				}
			}
		}

		if (Pop_BlueY == Pop_RedY) { // 두 공의 열(세로)이 같을 경우 : 상/하 판단후 가로 좌표 같으면 후처리
			bool BLUE_TOP; // 상/하 판단
			if (Pop_BlueX < Pop_RedX) {
				BLUE_TOP = true;
			}
			else {
				BLUE_TOP = false;
			}
			// 후처리
			if (Up_MoveBlueX == Up_MoveRedX && (HX != Up_MoveBlueX || HY != Up_MoveBlueY)) {
				if (BLUE_TOP) {
					Up_MoveRedX++;
				}
				else {
					Up_MoveBlueX++;
				}
			}
			if (Down_MoveBlueX == Down_MoveRedX && (HX != Down_MoveBlueX || HY != Down_MoveBlueY)) {
				if (BLUE_TOP) {
					Down_MoveBlueX--;
				}
				else {
					Down_MoveRedX--;
				}
			}
		}
		// 방문하지 않은 위치이면서, 파란 공이 홀컵에 들어가지 않았으면서, 10회 내의 경우만 deque에 push 후 방문처리
		if (!visited[Left_MoveBlueX][Left_MoveBlueY][Left_MoveRedX][Left_MoveRedY] && (Left_MoveBlueX != HX || Left_MoveBlueY != HY) && Pop_trial <= 9) {
			visited[Left_MoveBlueX][Left_MoveBlueY][Left_MoveRedX][Left_MoveRedY] = true;
			dq.push_back({ Left_MoveBlueX, Left_MoveBlueY, Left_MoveRedX, Left_MoveRedY, Pop_trial + 1});
		}
		if (!visited[Right_MoveBlueX][Right_MoveBlueY][Right_MoveRedX][Right_MoveRedY] && (Right_MoveBlueX != HX || Right_MoveBlueY != HY) && Pop_trial <= 9) {
			visited[Right_MoveBlueX][Right_MoveBlueY][Right_MoveRedX][Right_MoveRedY] = true;
			dq.push_back({ Right_MoveBlueX, Right_MoveBlueY, Right_MoveRedX, Right_MoveRedY, Pop_trial + 1});
		}
		if (!visited[Up_MoveBlueX][Up_MoveBlueY][Up_MoveRedX][Up_MoveRedY] && (Up_MoveBlueX != HX || Up_MoveBlueY != HY) && Pop_trial <= 9) {
			visited[Up_MoveBlueX][Up_MoveBlueY][Up_MoveRedX][Up_MoveRedY] = true;
			dq.push_back({ Up_MoveBlueX, Up_MoveBlueY, Up_MoveRedX, Up_MoveRedY, Pop_trial + 1});
		}
		if (!visited[Down_MoveBlueX][Down_MoveBlueY][Down_MoveRedX][Down_MoveRedY] && (Down_MoveBlueX != HX || Down_MoveBlueY != HY) && Pop_trial <= 9) {
			visited[Down_MoveBlueX][Down_MoveBlueY][Down_MoveRedX][Down_MoveRedY] = true;
			dq.push_back({ Down_MoveBlueX, Down_MoveBlueY, Down_MoveRedX, Down_MoveRedY, Pop_trial + 1});
		}

	}
	if (failure) {
		cout << "-1";
	}
}

int main() {
	cin >> X_SIZE >> Y_SIZE;
	MAP.resize(X_SIZE, vector<char>(Y_SIZE));
	char c;
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			cin >> c;
			MAP[i][j] = c;
			if (c == 'B') {
				BX = i; BY = j;
				MAP[i][j] = '.';
			}
			else if (c == 'R') {
				RX = i; RY = j;
				MAP[i][j] = '.';
			}
			else if (c == 'O') {
				HX = i; HY = j;
			}
		}
	}
	BFS();
}