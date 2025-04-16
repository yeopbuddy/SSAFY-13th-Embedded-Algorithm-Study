#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define MAX_N 100

struct Info {
	int s, d, b;
};

int N, M, K;
Info arr[MAX_N][MAX_N];
vector<Info> arrTmp[MAX_N][MAX_N];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int result = 0;

/*
상어를 잡아 봅시다~!
cath_gompang: y열의 상어를 잡습니다.
total_move: 모든 상어를 움직입니다.
merge: 상어를 합칩니다~!

그냥 시키는대로 하면 됩니다. 쓱싹
*/

void catch_gompang(int y) {
	for (int x = 0; x < N; x++) {
		if (arr[x][y].b > 0) {
			result += arr[x][y].b;
			arr[x][y] = { 0, 0, 0 };
			return;
		}
	}
}

bool bound_check(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

void move(int x, int y) {
	Info now = arr[x][y];
	
	int nx, ny;
	int nowX = x, nowY = y;
	for (int i = 0; i < now.s; i++) {
		nx = nowX + dx[now.d];
		ny = nowY + dy[now.d];

		if (!bound_check(nx, ny)) {
			if (now.d <= 1) {
				now.d = 1 - now.d;
			}
			else {
				now.d = 3 - now.d + 2;
			}

			nowX += dx[now.d];
			nowY += dy[now.d];

		}
		else {
			nowX = nx;
			nowY = ny;
		}
	}

	arrTmp[nowX][nowY].push_back(now);

	arr[x][y] = { 0, 0, 0 };
}

void total_move() {
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (arr[x][y].b > 0) {
				move(x, y);
			}
		}
	}
}

void merge() {
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (arrTmp[x][y].empty()) continue;
			Info max = { 0, 0, -1 };

			for (const Info &info : arrTmp[x][y]) {
				if (max.b < info.b) {
					max = info;
				}
			}

			arr[x][y] = max;
			arrTmp[x][y].clear();
		}
	}
}

void simulation(int y) {
	catch_gompang(y);

	total_move();

	merge();
}

int main(void) {
	fastio;

	cin >> N >> M >> K;

	int x, y, s, d, b;
	for (int i = 0; i < K; i++) {
		cin >> x >> y >> s >> d >> b;
		arr[x - 1][y - 1] = { s, d - 1, b };
	}

	for (int y = 0; y < M; y++) {
		simulation(y);
	}

	cout << result << '\n';

	return 0;
}