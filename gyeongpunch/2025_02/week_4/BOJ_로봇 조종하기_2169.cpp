#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// 손으로 그리다보니 점화식을 찾을 수 있었습니다.
// 누적합을 구해서 경로의 합을 빠르게 찾습니다.
// k: arr[i-1][k]에서 아래로 내려오는 지점
// k <= j 라면 i번째 행의 경로합은 sum[i][j + 1] - sum[i][k]가 됩니다.

// 연산이 오래걸려서 k < j일 때의 최대값을 따로 저장합니다.

const int MX_SZ = 1000;
const int INF = -1e9;

int N, M;
int arr[MX_SZ][MX_SZ];
int dp[2][MX_SZ][MX_SZ];
int sum[MX_SZ][MX_SZ+1];

int main(void) {
	fastio;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			sum[i][j + 1] = sum[i][j] + arr[i][j];
			dp[0][i][j] = INF;
			dp[1][i][j] = INF;
		}
	}

	for (int i = 0; i < M; i++) {
		dp[0][0][i] = sum[0][i + 1];
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dp[0][i][j] = dp[1][i][j] = max(dp[0][i - 1][j], dp[1][i - 1][j]) + arr[i][j];

			for (int k = j + 1; k < M; k++) {
				dp[1][i][j] = max(dp[1][i][j], max(dp[0][i - 1][k], dp[1][i - 1][k]) + sum[i][k + 1] - sum[i][j]);
			}
			if (j > 0) {
				dp[0][i][j] = max(dp[0][i][j], dp[0][i][j - 1] + arr[i][j]);
			}
		}
	}


	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << dp[0][i][j] << ' ';
		}
		cout << '\n';
	}
	*/

	cout << dp[0][N - 1][M - 1] << '\n';

	return 0;
}