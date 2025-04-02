#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// dp 테이블 정의: dp[i] : i번째 전깃줄까지 봤을 때 교차하지 않은 전깃줄 개수
// arr를 시작점 오름차순으로 정렬을 한 뒤, 끝점만 비교하여 교차하는지 안 하는지 판단합니다.
// arr[i].end > arr[j].end 라면 arr[i]와 arr[j]는 만나지 않는 전깃줄입니다.
// 그럼 dp[i]는 dp[j] + 1과 dp[i] 중 더 큰 값으로 채워지게 됩니다.
// dp 중 최대값은 안전한 전깃줄 수의 최댓값이므로 제거해야하는 전깃줄의 최소값은 N-max(dp)입니다.

// 와 너무 어렵다. 쉬운듯 어렵고,,,

struct Line{
    int start, end;
};

const int MX_N = 100;

int N;
Line arr[MX_N];
int dp[MX_N];

bool custom_compare(Line a, Line b){
    return a.start < b.start;
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> arr[i].start >> arr[i].end;
    }

    sort(arr, arr+N, custom_compare);

    int mx = 1;

    fill(dp, dp+N, 1);

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i].end > arr[j].end) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        mx = max(mx, dp[i]);
    }

    cout << N - mx << '\n';


    return 0;
}