#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// 이렇게 풀어야하나,,, 풀면서 자괴감이 들어요.
// 1. 모든 col의 첫 번째 row에 ballNum을 넣습니다.
// 2. drop하자.
// 3. 남아있는 공을 기준으로 rowSize와 colSize를 계산해서 arr[x][y]와 같으면 터집니다.
// 4. arrTmp를 이용해서 동시에 터지는 것을 처리합니다.
// 5. 남아있는 공을 카운트합니다.

const int N = 7;

int arrOrigin[N][N];
int arr[N][N];
int arrTmp[N][N];
int ballNum;

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = arrOrigin[i][j];
		}
	}
}

void drop() {
	for (int i = 0; i < N; i++) {
		int tmpIdx = N - 1;
		for (int j = N - 1; j > -1; j--) {
			if (arr[j][i] > 0) {
				if (j == tmpIdx) {
					tmpIdx--;
					continue;
				}
				arr[tmpIdx--][i] = arr[j][i];
				arr[j][i] = 0;
			}
		}
	}
}

bool bound_check(int x) {
	return 0 <= x && x < N;
}

int get_col_size(int x, int y) {
	int cnt = 1;
	int i = 1;
	while (bound_check(x - i) && arrTmp[x - i][y] != 0) {
		cnt++;
		i++;
	}
	i = 1;
	while (bound_check(x + i) && arrTmp[x + i][y] != 0) {
		cnt++;
		i++;
	}

	return cnt;
}

int get_row_size(int x, int y) {
	int cnt = 1;
	int i = 1;
	while (bound_check(y - i) && arrTmp[x][y - i] != 0) {
		cnt++;
		i++;
	}
	i = 1;
	while (bound_check(y + i) && arrTmp[x][y + i] != 0) {
		cnt++;
		i++;
	}

	return cnt;
}

bool crush() {
	bool flag = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arrTmp[i][j] = arr[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arrTmp[i][j] > 0) {
				int rowSize = get_row_size(i, j);
				int colSize = get_col_size(i, j);

				if (arrTmp[i][j] == rowSize || arrTmp[i][j] == colSize) {
					arr[i][j] = 0;
					flag = true;
				}
			}
		}
	}

	return flag;
}

int calc() {
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] > 0) {
				cnt++;
			}
		}
	}
	
	return cnt;
}

int simulation(int col) {
	if (arr[0][col] != 0) return -1;

	arr[0][col] = ballNum;

	while (true) {
		drop();
		if (!crush()) {
			break;
		}
	}

	int cnt = calc();

	return cnt;
}

int main(void) {
	fastio;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arrOrigin[i][j];
		}
	}

	cin >> ballNum;

	int result = N * N;
	for (int i = 0; i < N; i++) {
		init();
		int rest = simulation(i);
		result = min(result, rest);
	}

	cout << result << '\n';

	return 0;
}