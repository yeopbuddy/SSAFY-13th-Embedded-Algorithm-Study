#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);
using namespace std;

// 3개의 용액을 골라서 0에 가장 가까운 경우를 찾는 문제입니다.
// 일단 하나를 골라서 나머지 중에서 2개를 골라서 0에 가까운 수를 찾아봅시다.
// 투포인터를 사용하기 위해 배열을 정렬해서 3개의 용액의 합이 0보다 크면 e index를 줄이고 0보다 작으면 s index를 증가시킵니다.
// 모두 10억인 경우 int형을 사용하면 type overflow가 발생하므로 long long으로 sum값을 선언합니다.
// Struct = {x, y, z} 이게 안 된다고 합니다. 객체를 생성하는 거라고 하네요. 그냥 하나하나 대입하겠습니다.
// abs는 int형을 반환한다고 합니다. llabs를 사용하여 type overflow를 방지합시다.
// sum 값이 0일 때 Mn.sm가 0이면 break하니까 풀렸습니다. 그런데 왜 그런거지,,, 정답을 알려줘~_~

const int MAX = 5000;
const long long SUM_MAX = 3000000001;

int N;
long long arr[MAX];

struct Three{
    int f, s, t;
    long long sm;
};

int main(void){
    fastio;

    // freopen("input.txt", "r", stdin);

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }

    sort(arr, arr+N);

    Three Mn;
    Mn.sm = SUM_MAX;
    bool Is_finish = false;
    for(int i=0; i<N-2; i++){
        int s = i+1, e = N-1;
        while(s < e){
            long long sm = arr[i] + arr[s] + arr[e];
            if(llabs(sm) < Mn.sm){
                Mn.f = i;
                Mn.s = s;
                Mn.t = e;
                Mn.sm = llabs(sm);
            }
            if(Mn.sm == 0){
                Is_finish = true;
                break;
            }

            if(sm > 0){
                e--;
            }
            else{
                s++;
            }
        }
        if(Is_finish){
            break;
        }
    }

    cout << arr[Mn.f] << ' ' << arr[Mn.s] << ' ' << arr[Mn.t] << '\n';

    return 0;
}