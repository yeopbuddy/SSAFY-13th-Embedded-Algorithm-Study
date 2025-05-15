#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int TC;
    cin >> TC;
    while (TC--) {
        int k;
        cin >> k;
        vector<int> files(k);
        vector<vector<int>> sum(k, vector<int>(k));  // 구간 합 저장
        vector<vector<int>> dp(k, vector<int>(k, 0)); // dp[i][j]: i~j를 합치는데 드는 최소비용

        for (int i = 0; i < k; ++i) {
            cin >> files[i];
            sum[i][i] = files[i];
        }

        // 누적합 미리 계산
        for (int i = 0; i < k; ++i) {
            for (int j = i + 1; j < k; ++j) {
                sum[i][j] = sum[i][j - 1] + files[j];
            }
        }

        // DP
        for (int len = 2; len <= k; ++len) {
            for (int i = 0; i <= k - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = 1e9;
                for (int mid = i; mid < j; ++mid) {
                    dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j] + sum[i][j]);
                }
            }
        }

        cout << dp[0][k - 1] << "\n";
    }
}
