#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// 중복순열을 만들어서 5번 이동시키고 최대값을 찾아봅시다.
// 반시계 회전 rotate 함수를 만듭니다.
// 아래: 0, 왼쪽: 1, 위쪽: 2, 오른쪽: 3

// d가 0이면 drop만 합니다.
// 1이상이면 d만큼 회전 후 drop하고 4-d만큼 회전합니다.

// drop함수는 rowTmp(내려올 위치)가 N-1이면 그냥 쭉 내려옵니다.
// N-1이 아니면 합쳐질 수 있나 없나 확인합니다.
// 합쳐질 수 있으면 rowTmp는 그대로두고 rowTmp+1에 있는 값을 2배 후, row에 있는 값을 0으로 만듭니다.
// 합칠 수 없으면 rowTmp에 내리고 row에 있는 값을 0으로 만듭니다.

struct Node {
	int num;
	bool isavail;
};

const int MAX_N = 20;
const int MAX_DEPTH = 5;
int N;
int arrOrigin[MAX_N][MAX_N];
Node arr[MAX_N][MAX_N];
int arrTmp[MAX_N][MAX_N];
vector<vector<int>> dirPermu;
int result = 0;

void makePermutation(int depth, vector<int> &path) {
	if (depth == MAX_DEPTH) {
		dirPermu.push_back(path);
		return;
	}
	for (int i = 0; i < 4; i++) {
		path.push_back(i);
		makePermutation(depth + 1, path);
		path.pop_back();
	}
}

void initArr() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = { arrOrigin[i][j], true };
		}
	}
}

// 반시계 방향 회전
void rotate() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arrTmp[i][j] = arr[j][N - i - 1].num;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j].num = arrTmp[i][j];
		}
	}
}

void drop() {
	for (int col = 0; col < N; col++) {
		int rowTmp = N - 1;
		for (int row = N - 1; row > -1; row--) {
			if (arr[row][col].num > 0) {
				if (rowTmp == N - 1) {
					if (rowTmp == row) {
						rowTmp--;
					}
					else {
						arr[rowTmp--][col].num = arr[row][col].num;
						arr[row][col].num = 0; 
					}

				}
				else {
					if (arr[row][col].num == arr[rowTmp + 1][col].num && arr[rowTmp + 1][col].isavail) {
						arr[rowTmp + 1][col].num *= 2;
						arr[rowTmp + 1][col].isavail = false;
						arr[row][col].num = 0;
					}
					else {
						if (rowTmp == row) {
							rowTmp--;
						}
						else {
							arr[rowTmp--][col].num = arr[row][col].num;
							arr[row][col].num = 0;
						}
					}
				}
			}
		}
	}
}

void simulation() {
	for (const vector<int> &dirs : dirPermu) {
		initArr();

		for (const int &d : dirs) {

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					arr[i][j].isavail = true;
				}
			}

			if (d == 0) {
				drop();
				continue;
			}

			for (int i = 0; i < d; i++) {
				rotate();
			}

			drop();

			for (int i = 0; i < 4 - d; i++) {
				rotate();
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result = max(result, arr[i][j].num);
			}
		}
	}
}



int main(void) {
	fastio;

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arrOrigin[i][j];
		}
	}

	vector<int> path;
	makePermutation(0, path);

	simulation();

	cout << result << '\n';

	return 0;
}