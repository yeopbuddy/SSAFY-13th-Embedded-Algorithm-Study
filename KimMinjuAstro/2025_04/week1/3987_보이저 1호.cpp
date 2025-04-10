#include<iostream>
#include<algorithm>
using namespace std;
int n, m;	// n행 m열
char map[501][501];
int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,1,0,-1 };
void init() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
}
int y, x, dir;
void input() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> map[i][j];
		}
	}
	cin >> y >> x;
}
int posSlash(int d) {
	if (d == 0)return 1;
	if (d == 1)return 0;
	if (d == 2)return 3;
	if (d == 3)return 2;
}
int negSlash(int d) {
	if (d == 0)return 3;
	if (d == 1)return 2;
	if (d == 2)return 1;
	if (d == 3)return 0;
}
int go(int d, int curY, int curX) {
	int curDir = d;
	int cnt = 1;
	while (1) {

		if (cnt > n * m * 2) {
			cnt = -1;
			break;
		}

		int ny = curY + ydir[curDir];
		int nx = curX + xdir[curDir];

		if (ny < 1 || ny > n || nx < 1 || nx > m)break;
		if (map[ny][nx] == 'C')break;
		if (map[ny][nx] == '/') curDir = posSlash(curDir);
		if (map[ny][nx] == '\\') curDir = negSlash(curDir);
		cnt++;

		curY = ny;
		curX = nx;
	}
	// cout << d << " 방향으로 갔을 때 " << cnt << "\n";
	return cnt;
}
void solution() {
	int maxSig = 0;
	int maxDir = -1;
	bool loop = false;
	char dir;
	for (int d = 0; d < 4; d++)
	{
		int curCnt = go(d, y, x);
		if (curCnt == -1) {
			loop = true;
			maxDir = d;
			break;
		}
		if (maxSig < curCnt) {
			maxSig = curCnt;
			maxDir = d;
		}
	}
	if (maxDir == 0)dir = 'U';
	if (maxDir == 1)dir = 'R';
	if (maxDir == 2)dir = 'D';
	if (maxDir == 3)dir = 'L';
	if (!loop) {

		cout << dir << "\n" << maxSig;
	}
	else {
		cout << dir << "\n" << "Voyager";
	}
}
int main() {
	init();
	input();
	solution();
}