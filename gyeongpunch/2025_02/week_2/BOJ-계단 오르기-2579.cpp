#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
    int N;
    cin >> N;
    vector<int> arr(N+1, 0);
    vector<int> dp(N+1, 0);
    for(int i=1; i<=N; i++){
        cin >> arr[i];
    }
    dp[1] = arr[1];
    dp[2] = arr[1] + arr[2];

    int mx = 0;

    for(int i=3; i<=N; i++){
        dp[i] = max(dp[i-2], dp[i-3]+arr[i-1]) + arr[i];
    }

    cout << dp[N] << endl;

    return 0;
}