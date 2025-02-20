// 2473번 세 용액
// 정렬, 투포인터
/*
접근 방법:
정렬 후 하나 고정 후 투포인터로 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
typedef long long ll;

int main(void){
    int N; cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(A.begin(), A.end());
    ll x, y, z, m = 3'000'000'000;
    for (int i = 0; i < N-2; i++){
        int s = i+1, e = N-1;
        while (s < e){
            ll d = A[i]+A[s]+A[e];
            if (abs(d) < m){
                m = abs(d);
                x = A[i], y = A[s], z = A[e];
            }
            if (d < 0) s++;
            else e--;
        }
    }
    cout << x << ' ' << y << ' ' << z;
    return 0;
}