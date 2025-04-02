#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

struct Point {
	int x, y;
};

const int MAX_SZ = 10;

int N, M;
char arr[MAX_SZ][MAX_SZ];
Point red, blue, OUT;
int result = 11;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

/*
중복순열 + 시뮬레이션. 근데 이제 가지치기를 곁들인.

맵을 기울였을 때, 바뀌는 것은 빨간 구슬, 파란구슬의 좌표 밖에 없어서 이 둘만 관리하게 Point red, blue를 선언했습니다.
그러고 초기 구슬 위치는 '.' 으로 채웠습니다.


구슬이 빠지면 좌표를 {-1, -1}로 저장하여 빠진 구슬인지 아닌지를 판단합니다.
파란 구슬이 빠졌으면 아묻따 실패입니다.
파란 구슬이 안 빠지고 빨간 구슬이 빠졌으면 현재까지의 턴인 depth로 result를 업데이트 합니다.


# gogo함수
Tilt함수로 derection을 정해서 해당 방향으로 기울여서 구슬을 이동시킵니다. 근데 이제 가지치기를 곁들인
1. depth가 10 이상이면 당연히 멈춰야합니다.
2. depth가 현재의 result 이상이면 더이상 볼 필요가 없습니다.
3. 이전의 방향을 다시 Tilt 할 필요가 없습니다.
4. 둘 다 이동할 수 없으면 그 방향으로 Tilt 할 필요가 없습니다.
 * isBothMove 함수: 둘 다 이동할 수 없는지, 하나라도 움직일 수 있는지 판단하는 함수

위에의 가지치기에 안 걸러지면 해당 방향으로 Tilt해줍니다.
근데 이제 재귀가 끝나고 돌아왔을 때의 구슬 좌표를 기억하기 위해 redTmp, blueTmp에 저장해줍니다.


# tilt함수
구슬들의 좌표를 전역 구조체에 따로 보관하고 있기 때문에 tilt를 할 때 방향에 따라 무엇을 먼저 이동시켜야하는지 판단해야합니다.
 * isRedFirst 함수: 빨간색을 먼저 이동해야하는지 아닌지를 판단하는 함수
 
dir이 0(위로)이면 빨간색 구슬의 row가 더 작아야 빨간색이 먼저 이동합니다.
dir이 1(오른쪽)이면 빨간색 구슬의 col이 더 커야 빨간색이 먼저 이동합니다.
dir이 2(아래)면 빨간색 구슬의 row가 더 커야 먼저 이동합니다.
dir이 3(왼쪽)이면 빨간색 구슬의 col이 더 작아야 빨간색이 먼저 이동합니다.


이제 진짜 goosleMove 함수로 구슬을 이동시켜봅시다.

# goosleMove함수
1. 벽에 부딪힐 때까지
2. 구슬에 부딪힐 때까지
dir 방향으로 쭉 이동합니다.
*/

bool isRedFirst(int dir) {
	if (dir == 0) {
		if (red.y == blue.y) {
			if (red.x < blue.x) return true;
			else return false;
		}
		else return true;
	}

	else if (dir == 1) {
		if (red.x == blue.x) {
			if (red.y > blue.y) return true;
			else return false;
		}
		else return true;
	}

	else if (dir == 2) {
		if (red.y == blue.y) {
			if (red.x > blue.x) return true;
			else return false;
		}
		else return true;
	}

	else if (dir == 3) {
		if (red.x == blue.x) {
			if (red.y < blue.y) return true;
			else return false;
		}
		else return true;
	}
}

void goosleMove(Point &goosle, int dir) {
	int nx, ny;
	while (true) {
		nx = goosle.x + dx[dir];
		ny = goosle.y + dy[dir];
		if (arr[nx][ny] == '#') break;
		if (nx == red.x && ny == red.y) break;
		if (nx == blue.x && ny == blue.y) break;

		if (arr[nx][ny] == 'O') {
			goosle = { -1, -1 };
			break;
		}

		goosle.x = nx;
		goosle.y = ny;
	}
}

void tilt(int dir) {
	if (isRedFirst(dir)) {
		goosleMove(red, dir);
		goosleMove(blue, dir);
	}
	else {
		goosleMove(blue, dir);
		goosleMove(red, dir);
	}
}

void pprint() {
	cout << "===============================\n";

	cout << "red 좌표: " << red.x << ' ' << red.y << '\n';
	cout << "blue 좌표: " << blue.x << ' ' << blue.y << '\n';

	cout << "===============================\n";
}

bool isBothMove(int dir) {
	int rnx = red.x + dx[dir], rny = red.y + dy[dir];
	int bnx = blue.x + dx[dir], bny = blue.y + dy[dir];

	if (arr[rnx][rny] != '#' || arr[bnx][bny] != '#') {
		if ((rnx == blue.x && rny == blue.y) && (bnx == red.x && bny == red.y)) {
			return false;
		}
		return true;
	}
	return false;
}

void gogo(int depth, int prevDir) {
	if (blue.x == -1 && blue.y == -1) return;

	if (red.x == -1 && red.y == -1) {
		result = min(result, depth);
		return;
	}

	if (depth >= 10) return;
	if (depth >= result) return;

	for (int i = 0; i < 4; i++) {
		if (i == prevDir) continue;
		if (!isBothMove(i)) continue;

		Point redTmp = red;
		Point blueTmp = blue;

		tilt(i);

		gogo(depth + 1, i);

		red = redTmp;
		blue = blueTmp;
	}
}

int main(void) {
	fastio;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 'R') {
				red = { i, j };
				arr[i][j] = '.';
			}
			else if (arr[i][j] == 'B') {
				blue = { i, j };
				arr[i][j] = '.';
			}
			else if (arr[i][j] == 'O') {
				OUT = { i, j };
			}
		}
	}
	
	gogo(0, -1);

	if (result == 11) result = -1;

	cout << result << '\n';

	return 0;
}