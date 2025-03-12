// 17297번 Messi Gimossi
// 재귀, 탑다운 DP
/*
접근 방법:
DP[i] = messi(i)의 길이 라고 정의합시다.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
#define LIMIT (1 << 30) - 1
typedef long long ll;

string Messi(const vector<ll>& DP, ll N){
    if (N <= 13){
        // 빈 문자열이면
        if (N == 6) return "Messi Messi Gimossi"; //메시메시기모찌
        else return string(1, "Messi Gimossi"[N-1]);
    }
    else {
        for (auto messiLen: DP){
            if (messiLen+1 == N){
                return "Messi Messi Gimossi"; // 빈 칸인 경우
            }
        }
        int i = 0;
        while (i < DP.size() && DP[i] < N) ++i;
        --i;
        return Messi(DP, N-1-DP[i]);
    }
}

int main(void){
    fastio;
    ll N; cin >> N;
    vector<ll> DP = {5, 13};
    int i = 2;
    while (true){
        ll k = DP[i-1] + 1 + DP[i-2];
        if (k > LIMIT) break;
        DP.push_back(k);
        ++i;
    }
    cout << Messi(DP, N);
}