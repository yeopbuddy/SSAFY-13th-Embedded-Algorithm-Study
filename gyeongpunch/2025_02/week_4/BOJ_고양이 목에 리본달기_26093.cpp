#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// 1등 만족도 리본과 2등 만족도 리본을 찾습니다.
// 1등 만족도 리본과 같은 종류이면 2등 만족도 리본을 선택하고 나머지는 다 1등 만족도 리본을 선택합니다.

// 이제 최적화해봅시다.
// 매 고양이 마다 이전까지의 1등 만족도 리본 2등 만족도 리본을 찾는 것이 다소 비효율적인 것 같습니다.
// 그때 그때마다 prev_big1, prev_big2에 이전까지의 만족도 1, 2등 리본을 찾습니다.

// dp도 2차원일 필요가 없을 것같아요. 이전의 1, 2등을 prev가 가지고 있으니까 1차원으로 해결가능합니다.
// big1에는 지금까지의 최대값이 들어있으니까 초기화하기 전에 break하여 다시 최대값을 찾지 않게 합니다.

struct Ribbon {
	int value, idx;
};

const int MX_N = 100;
const int MX_K = 10000;

int arr[MX_K];
int dp[MX_K];
int N, K;

Ribbon big1 = { -1, -1 }, big2 = { -1, -1 };
Ribbon prev_big1 = { 0, -1 }, prev_big2 = { 0, -1 };

int main(void) {
	fastio;

	cin >> N >> K;

	for (int i = 1; i <= N; i++) {

		for (int j = 0; j < K; j++) {
			cin >> arr[j];

			if (prev_big1.idx == j) {
				dp[j] = prev_big2.value + arr[j];
			}
			else {
				dp[j] = prev_big1.value + arr[j];
			}

			if (big1.value <= dp[j]) {
				big2.value = big1.value;
				big2.idx = big1.idx;

				big1.value = dp[j];
				big1.idx = j;
			}
			else if (big2.value < dp[j]) {
				big2.value = dp[j];
				big2.idx = j;
			}


		}
		prev_big1 = big1;
		prev_big2 = big2;

		if (i == N) {
			break;
		}

		big1.value = big2.value = 0;
	}
	
	cout << big1.value << '\n';

	return 0;
}