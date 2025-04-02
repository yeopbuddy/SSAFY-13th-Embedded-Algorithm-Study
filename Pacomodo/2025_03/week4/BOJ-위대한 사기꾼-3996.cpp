// 3996번 위대한 사기꾼
// 수학
/*
접근 방법:
    a_{0} + a_{1}k^{1} + a_{2}k^{2} + ... + a_{p}k^{p}
=   a_{0} - a_{1}k^{1} + a_{2}k^{2} + ... + a_{p}k^{p}
위의 조건을 만족해야 합니다.
이를 만족하기 위해서는, k진법으로 전개한 짝수번째 항(a_{1},...)들이 모두 0이어야 합니다.
그 외의 조건은 신경쓸 필요가 없습니다.
따라서, 조합론적으로 바라볼 수 있습니다.

예제 입력 1의 경우 다음과 같습니다. 
21 3
21을 3진법으로 나타낼 경우,
210_{3}이 됩니다.
따라서, 가운데 짝수번째 항만 0이 되면 됩니다.
X0X -> 따라서 X에 들어갈 수 있는 수는 3*3 = 9가지이므로, 9개가 답이 됩니다.

접근 방식은 다음과 같습니다. 
1. 먼저 N을 k진법으로 표현합니다.
2. k진법으로 표현했을 때 몇 자리수 숫자인지 생각해봅시다.
편의 상 몇 자리인지를 p라고 합시다.
2-1. 만약 p가 짝수라면
-> 0X0X0X0X...0X꼴이어야 합니다. 즉, 가장 큰 자리수의 숫자가 0이어야 합니다.
그 외에는 k보다 작은 어떠한 숫자도 올 수 있으므로,
k^{p/2}가 답이 됩니다.
2-2. 만약 p가 홀수라면
-> a_{p}0X0...0X꼴입니다.
즉, (가장 큰 자리수의 숫자(a_{p})) * k^{p/2}가 기본 베이스가 됩니다.
여기에 가장 큰 자리수의 숫자를 a_{p}로 고정하고 N보다 작은 모든 경우의 수를 더해줍시다.
*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
typedef long long ll;

int main(void){
    fastio;
    ll n, k; cin >> n >> k;
    ll p = 0, largest = 0;
    vector<ll> A;
    while (n > 0){
        if (n < k) largest = n;
        A.push_back(n % k);
        n /= k;
        ++p;
    }
    if (p == 1){
        cout << largest+1;
        return 0;
    }
    ll ans = 1;
    for (int i = 0; i < p/2; ++i){
        ans *= k;
    }
    if (p % 2){
        ans *= largest;
        A.pop_back();
        --p;
        while (p){
            if (A.back() != 0){
                ll remain = 1;
                for (int i = 0; i < p/2; ++i){
                    remain *= k;
                }
                ans += remain;
                break;
            }
            A.pop_back();
            --p;
            ll r = A.back();
            if (p == 1){
                ans += (r+1);
                break;
            }
            for (int i = 0; i < p/2; ++i){
                r *= k;
            }
            ans += r;
            A.pop_back();
            --p;
        }
    }
    cout << ans;
    return 0;
}