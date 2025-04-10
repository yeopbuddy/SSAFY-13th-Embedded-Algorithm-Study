#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// arr.arr1: 석순, arr.arr2: 종유석
// 석순은 내림차순, 종유석은 오름차순으로 정렬합니다.
// 각 동굴 높이마다의 장애물을 dp[0] 배열, dp[1] 배열열에 저장합니다.

// idx1: 석순 인덱스, idx2: 종유석 인덱스
// 동굴의 높이 반복문을 돌리면서 M - idx1번째 석순보다 동굴의 높이가 크면 석순 dp배열을 증가시켜줍니다.
// 같은 높이가 여러개 있을 수 있으므로 while문으로 처리하여 석순 dp배열을 증가시켜줍니다.

// 종유석은 내림차순으로 정렬했으므로 초기값은 N/2로 저장합니다.
// 동굴의 높이 반복문을 돌리면서 idx2번째 석순보다 동굴의 높이가 커지면 종유석 dp배열을 감소시켜줍니다.
// 종유석 또한 같은 높이가 여러개 있을 수 있으므로 while문으로 처리하여 종유석 dp배열을 감소시켜줍니다.

// dp[0][i], dp[0][i] 번째에 값이 들어있으므로 최솟값을 계산해줍니다.


const int MAX_N = 200000;
const int MAX_H = 500000;

struct Arr {
	int arr1[MAX_N / 2];
	int arr2[MAX_N / 2];
};

int dp[2][MAX_H + 2];

int N, M;
Arr arr;

int main(void) {
	fastio;

	cin >> N >> M;
	for (int i = 0; i < N / 2; i++) {
		cin >> arr.arr1[i] >> arr.arr2[i];
	}

	sort(arr.arr1, arr.arr1 + N / 2, greater<>());
	sort(arr.arr2, arr.arr2 + N / 2);

	int idx1 = 0, idx2 = 0;
	int minValue = 1e9;
	int minCnt = 0;
	dp[1][0] = N / 2;

	for (int i = 1; i <= M; i++) {
		if (idx1 < N / 2) {
			dp[0][i] = dp[0][i - 1];
			while (idx1 < N / 2 && M - arr.arr1[idx1] < i) {
				dp[0][i]++;
				idx1++;
			}
		}
		else {
			dp[0][i] = dp[0][i - 1];
		}

		if (idx2 < N / 2) {
			dp[1][i] = dp[1][i - 1];
			while (idx2 < N / 2 && i > arr.arr2[idx2]) {
				dp[1][i]--;
				idx2++;
			}
		}
		else {
			dp[1][i] = dp[1][i - 1];
		}

		if (dp[0][i] + dp[1][i] < minValue) {
			minValue = dp[0][i] + dp[1][i];
			minCnt = 1;
		}
		else if (dp[0][i] + dp[1][i] == minValue) {
			minCnt++;
		}
	}

	cout << minValue << ' ' << minCnt << '\n';


	return 0;
}