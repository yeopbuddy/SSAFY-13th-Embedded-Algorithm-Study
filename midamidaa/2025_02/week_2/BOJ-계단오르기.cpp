#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<algorithm>

using namespace std;

int n;

int stairs[303] = { 0, };

// 한 계단 전을 밟거나, 두 계단 전을 밟거나 둘 중 하나밖에 없음
// first: 한 계단 전 밟았을 경우 최대 점수
// second: 두 계단 전 밟았을 경우 최대 점수
pair<int, int> dp[303];



int main() {

	int n;
	cin >> n;

	// stairs[1] 부터 첫 번째 계단
	for (int i = 1;i <= n;i++) {
		cin >> stairs[i];

	}

	dp[0].first = 0;
	dp[0].second = 0;

	dp[1].first = stairs[1];
	dp[1].second = stairs[1];

	dp[2].first = stairs[1] + stairs[2];
	dp[2].second = stairs[2];
	for (int i = 3;i <= n;i++) {
		dp[i].first = dp[i - 1].second + stairs[i];
		dp[i].second = max(dp[i - 2].first, dp[i - 2].second) + stairs[i];
	}

	cout << max(dp[n].first, dp[n].second);



}

