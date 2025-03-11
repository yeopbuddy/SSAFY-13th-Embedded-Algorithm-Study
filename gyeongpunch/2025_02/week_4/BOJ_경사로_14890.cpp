#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// 아오 중간에 꼬여서 시간 엄청 걸렸네요.
// idx번째 가로, 세로를 체크합니다.
// diff의 절댓값이 1초과이면 바로 false입니다.
// diff가 0이면 지나온 평평한 길의 개수인 cnt를 1더합니다.
// diff가 1이면 cnt와 L을 비교하여 cnt가 크거나 같으면 다시 cnt를 1로 두고 진행합니다.
// dirff가 -1이면 다른 루프를 돌게합니다. 내림막 경사로를 설치하면 마지막 칸에는 다른 경사로를 설치할 수 없으므로 cnt=0으로 둡니다.

const int MX_N = 100;

int N, L;
int arr[MX_N][MX_N];

bool garo(int idx){
    int cnt = 1, i = 0, diff, j;

    while(i < N-1){
        diff = arr[idx][i+1] - arr[idx][i];

        if(diff > 1 || diff < -1) return false;

        if(diff == 0) {
            cnt++;
        }
        else if(diff == 1){

            if(cnt >= L){
                cnt = 1;
            }
            else return false;
        }
        else if(diff == -1){
            j = 1;
            while(j <= L){
                if(arr[idx][i+j] != arr[idx][i]-1) return false;

                j++;
            }
            i += (j-1);
            cnt = 0;
            continue;
        }

        i++;
    }
    return true;
}

bool sero(int idx){
    int cnt = 1, i = 0, diff, j;

    while(i < N-1){
        diff = arr[i+1][idx] - arr[i][idx];

        if(diff > 1 || diff < -1) return false;

        if(diff == 0) {
            cnt++;
        }
        else if(diff == 1){

            if(cnt >= L){
                cnt = 1;
            }
            else return false;
        }
        else if(diff == -1){
            j = 1;
            while(j <= L){
                if(arr[i+j][idx] != arr[i][idx]-1) return false;

                j++;
            }
            i += (j-1);
            cnt = 0;
            continue;
        }

        i++;
    }
    return true;
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N >> L;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
        }
    }

    int result = 0;
    for(int i=0; i<N; i++){
        if(garo(i)){
            result++;
            // cout << "garo: " << i << '\n';
        }
        if(sero(i)){
            result++;
            // cout << "sero: " << i << '\n';
        }
    }

    cout << result << '\n';

    return 0;
}