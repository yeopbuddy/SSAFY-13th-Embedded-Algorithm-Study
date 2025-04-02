#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// 전형적인 구현 문제입니다. 시키는대로 하는데 이동한 미친 아두이노의 위치에 visited[x][y]++를 하고
// 이 값이 2 이상이면 폭파하여 정확히 1인 미친 아두이노만 살아남게 하였습니다.

// 이제 최적화해봅시다. 매 턴마다 미친 아두이노의 위치가 조정되므로 queue를 이용하면 mad_arduino.clear()를 안 해도되니 편리할 것 같습니다.
// visited 배열을 매 턴마다 memeset을 해주고 visited[x][y]==1인 모든 칸을 순회하는 것이 비효율적인 것 같습니다.
// 미친 아두이노가 이동한 위치를 벡터에 저장하고 visited[x][y] == 1이면 queue에 push하면서 0으로 만들고, 이 이상이면 그냥 0으로 만듭시다.

// 나름 최적화했는데 1ms도 안 줄어드네ㅜㅜ

const int MAX_SIZE = 100;

struct Loc{
	int x, y;
};

int N, M;
char arr[MAX_SIZE][MAX_SIZE];
char visited[MAX_SIZE][MAX_SIZE] = { 0 };
queue<Loc> mad_arduino;
Loc cur;
string cmds;
int dx[9] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };
int dy[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
Loc mad_loc[MAX_SIZE * MAX_SIZE];

bool move(int cmd) {
	cur.x += dx[cmd];
	cur.y += dy[cmd];

	int mad_cnt = 0;
	while (!mad_arduino.empty()) {
		Loc l = mad_arduino.front(); mad_arduino.pop();

		if (l.x == cur.x && l.y == cur.y) return true;

		if (l.x < cur.x) {
			l.x++;
		}
		else if (l.x > cur.x) {
			l.x--;
		}

		if (l.y < cur.y) {
			l.y++;
		}
		else if (l.y > cur.y) {
			l.y--;
		}

		if (l.x == cur.x && l.y == cur.y) return true;
		
		visited[l.x][l.y]++;
		mad_loc[mad_cnt++] = {l.x, l.y};
	}

	int mx, my;
	for (int i = 0; i < mad_cnt; i++) {
		mx = mad_loc[i].x;
		my = mad_loc[i].y;
		if (visited[mx][my] == 1) {
			mad_arduino.push({ mx, my });
		}
		visited[mx][my] = 0;
	}

	return false;
}

void print_arr() {
	memset(arr, '.', sizeof(arr));

	arr[cur.x][cur.y] = 'I';
	while (!mad_arduino.empty()) {
		Loc l = mad_arduino.front(); mad_arduino.pop();
		arr[l.x][l.y] = 'R';
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << arr[i][j];
		}
		cout << '\n';
	}
}

void pprint() {
	cout << "=========================\n";
	cout << "My Position: " << cur.x << ' ' << cur.y << "\n\n";
	while (!mad_arduino.empty()) {
		Loc l = mad_arduino.front(); mad_arduino.pop();

		cout << l.x << ' ' << l.y << '\n';

		mad_arduino.push(l);
	}

	cout << "=========================\n";
}

int main(void) {
	fastio;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'I') {
				cur.x = i;
				cur.y = j;
			}
			else if (arr[i][j] == 'R') {
				mad_arduino.push({ i, j });
			}
		}
	}

	cin >> cmds;

	bool IsEnd;
	int i;
	for (i = 0; i < cmds.length(); i++) {
		IsEnd = move(cmds[i] - '0' -1);
		if (IsEnd) {
			break;
		}
	}

	if (IsEnd) {
		cout << "kraj " << i + 1 << '\n';
	}
	else {
		print_arr();
	}

	return 0;
}