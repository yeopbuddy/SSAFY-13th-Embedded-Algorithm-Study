// 1929번 소수 구하기
// 에테체
/*
접근 방법:
에테체로 소수 전처리
*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    // 에라토스테네스의 체
    vector<bool> sieve(1'000'001, 0);
    sieve[0] = 1, sieve[1] = 1;
    // 0과 1은 소수가 아니므로 방문해준다.
    for (int i = 2; i*i < 1'000'001; i++){
        // 소수라면
        if (!sieve[i]){
            // 소수의 배수들을 탐색한다. 소수의 배수는 모두 합성수다.
            for (int j = i*i; j < 1'000'001; j += i){
                sieve[j] = 1;
            }
        }
    }

    int M, N; cin >> M >> N;
    for (int i = M; i <= N; i++){
        if (!sieve[i]) cout << i << endl;
    }
    return 0;
}