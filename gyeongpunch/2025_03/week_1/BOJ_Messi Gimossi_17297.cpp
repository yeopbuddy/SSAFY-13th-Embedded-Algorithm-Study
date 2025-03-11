#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// MAX_N을 50으로 잡으니까 그냥 넉넉하게 최대 M보다 커지더라구요.
// 피보니치처럼 문자열의 길이를 저장하다가 M보다 커지거나 같아지면 멈춰서 함수를 돌립니다.
// arr[N] = arr[N-1] + 1 + arr[N-2]
// 1. target(몇 번째)이 arr[nowIdx - 1] + 1 과 같으면 공백이라는 뜻이므로 바로 리턴합니다.
// 2. target이 arr[nowIdx - 1] + 1보다 크면 arr[N-2] 중에 있다는 뜻이므로 dq함수를 다시 돌리는데
//      target이 target - arr[nowIdx - 1] - 1을 해서 dq를 돌립니다.
// 3. target이 arr[nowIdx - 1] + 1보다 작으면 arr[N-1] 중에 있다는 뜻이므로 nowIdx만 감소시켜서 dq를 돌립니다.

const int MAX_N = 50;

long long M;
long long arr[MAX_N];
char dq_result;

string str1 = "Messi";
string str2 = "Messi Gimossi";

void dq(int nowIdx, long long target){
    if(target <= 13){
        dq_result = str2[target - 1];
        return;
    }

    if(arr[nowIdx - 1] + 1 == target){
        dq_result = ' ';
        return;
    }

    else if(arr[nowIdx - 1] + 1 < target){
        dq(nowIdx-2, target - arr[nowIdx-1] - 1);
    }

    else{
        dq(nowIdx-1, target);
    }

}

char get_result(){
    if(M <= 13){
        return str2[M-1];
    }

    int idx;
    for(idx=3; idx<MAX_N; idx++){
        arr[idx] = arr[idx-1] + 1 + arr[idx-2];
        if(arr[idx] >= M) break;
    }

    dq(idx, M);

    return dq_result;
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> M;

    arr[1] = 5;
    arr[2] = 13;

    char result = get_result();

    if(result == ' '){
        cout << "Messi Messi Gimossi\n";
    }
    else{
        cout << result << '\n';
    }
    
    return 0;
}