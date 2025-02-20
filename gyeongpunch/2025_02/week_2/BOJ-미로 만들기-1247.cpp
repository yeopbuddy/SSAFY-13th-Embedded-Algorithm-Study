#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <queue>

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

using namespace std;

// 처음부터 좌표를 잡고 Map을 그리려면 배열 사이즈가 낭비되므로 0, 0을 기준으로 상대 위치를 구하고
// 모든 좌표를 구한 다음 offset 처리했습니다.
// Map의 Size는 [Mx.x - Mn.x + 1][Mx.y - Mn.y + 1]입니다.
// 각 칸끼리 공백이 없었군요,,,ㅎ

struct Point {
	int x, y;
};

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

char arr[50][50];

int main(void) {
	fastio;

	int N;
	cin >> N;
	string cmd;
	cin >> cmd;
	vector<Point> path;
	memset(arr, '#', sizeof(arr));

	int x = 0, y = 0, dir = 1;
	path.push_back({ x, y });

	Point Mn = { 0, 0 };
	Point Mx = { 0, 0 };
	for (char c : cmd) {
		if (c == 'R') {
			dir = (dir + 1) % 4;
		}
		else if (c == 'L') {
			dir = (dir + 3) % 4;
		}
		else if (c == 'F') {
			x += dx[dir];
			y += dy[dir];
			path.push_back({ x, y });
			Mn.x = min(Mn.x, x);
			Mn.y = min(Mn.y, y);
			Mx.x = max(Mx.x, x);
			Mx.y = max(Mx.y, y);
		}
	}

	for (Point p : path) {
		arr[p.x - Mn.x][p.y - Mn.y] = '.';
	}

	for (int i = 0; i <= Mx.x - Mn.x; i++) {
		for (int j = 0; j <= Mx.y - Mn.y; j++) {
			cout << arr[i][j];
		}
		cout << '\n';
	}

	return 0;
}