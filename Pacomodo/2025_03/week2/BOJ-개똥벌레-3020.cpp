// 3020번 개똥벌레
// 브루트포스, 이분탐색
/*
접근 방법: 
길이가 S인 종유석과 만나지 않는다 = 길이가 H-S인 석순과 만난다.
길이가 H-S인 석순과 만나지 않는다. = 길이가 S인 종유석과 만난다.

짝수번째(종유석)원소를 석순(H-S)으로 바꾼다.

이후 짝수번째끼리, 홀수번째끼리 분류. 
높이 h가 주어지면 홀수번째(석순)원소들이 몇개 만나는지는 정렬 후 이분탐색으로 확인 가능.
높이 h가 주어지면 짝수번째(석순)원소들이 몇개 만나는지는 정렬 후 이분탐색으로 확인 가능.
N/2 - (짝수번째 석순이 몇개 만나는 지) = 종유석 만나는 개수

즉, N/2 + (홀수번째 석순이 몇개 만나는지) - (짝수번째 석순이 몇개 만나는지) =
(개똥벌레가 파괴해야하는 장애물 개수)

이걸 모든 H마다 확인한다.
한번 확인할 때마다 이분탐색 한번임. 그 이분탐색은 log(20만)이다.

즉, 최종 시간 복잡도는
$\mathcal{O}(50만 \times \log(20만)) \approx \mathcal{O}(800만)$
대충 잘 돌아갈것 같다. 굳~
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    int N, H; cin >> N >> H;
    vector<int> odd(N/2);
    vector<int> even(N/2);
    int height;
    for (size_t i = 0; i < N; i++){
        cin >> height;
        if (i % 2) even.push_back(H-height);
        else odd.push_back(height);
    }
    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());
    int m = N+1, count = 0;
    for (size_t h = 1; h <= H; h++){
        int odd_meet = distance(upper_bound(odd.begin(), odd.end(), h), odd.end());
        int even_meet = distance(upper_bound(even.begin(), even.end(), h), even.end());
        int GAEDDONG_BREAK = N/2 + odd_meet - even_meet;
        if (GAEDDONG_BREAK < m){
            m = GAEDDONG_BREAK;
            count = 1;
        }
        else if (GAEDDONG_BREAK == m){
            ++count;
        }
    }
    cout << m << ' ' << count;
    return 0;
}