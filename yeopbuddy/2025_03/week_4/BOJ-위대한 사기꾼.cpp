#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// 민우님이 멱살잡고 알려주신거 기념 ..
vector<long long> Jungminwoo99; // 변환된 진수 저장
void numcvt(long long num, long long k){ // 레전드 진수 변환 ㅋㅋ
    long long top = 1; long long js = 1;
    while(true){
        if(top * k > num){
            break;    
        }
        top *= k; js++;
    }
    while(js != 0){
        for(long long i = k - 1; i >= 0; i--){
            if(num >= top * i){
                Jungminwoo99.push_back(i);
                num -= top * i;
                break;
            }
        }
        top /= k; js--;
    }
}

int main(){
    long long n, k; cin >> n >> k;
    numcvt(n, k); // n을 k진수로 변환하여 vector에 넣는다
    int i = ((Jungminwoo99.size() % 2) + 1) % 2; // vector size(진법 변환 후 자릿수) 짝 -> 1, 홀 -> 0
    bool carry = false;
    vector<int> mxnum; // n보다 같거나 작으면서 조건 만족하는 가장 큰 수 LSB부터 짝수 자리 숫자들만 저장
    for(i; i < Jungminwoo99.size(); i += 2){ // mxnum 구하는 논리
        if(!carry){
            if(i != 0 && Jungminwoo99[i-1] != 0){
                carry = true;
                mxnum.push_back(k-1);
            }   
            else{
                mxnum.push_back(Jungminwoo99[i]);
            }
        }
        else{
            mxnum.push_back(k-1);
        }
    }
    reverse(mxnum.begin(), mxnum.end()); // 진법 변환을 위해 돌려버려
    long long base = 1;
    long long ans = 0;
    for(long long val : mxnum){
        ans += base * val;
        base *= k;
    }
    cout << ans + 1; // 0도 포함해줌
    return 0;
}