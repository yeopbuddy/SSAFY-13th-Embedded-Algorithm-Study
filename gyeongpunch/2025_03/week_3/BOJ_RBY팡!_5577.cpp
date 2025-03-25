#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

#define MAX_N 10000

/*
터질 수 있는 모든 곳에서 터트려봅시다.

1. 오른쪽으로 같은 색 3개 이상
2. 왼쪽으로 같은 색 3개 이상
3. 오른쪽 + 왼쪽을 이어서 같은 색 3개 이상
일 때만 해당 색으로 바꿔서 시뮬을 돌려봅시다.

터트리는 simulation 함수에서 Info.n : 숫자, Info.cnt : 해당 숫자가 현재까지 연속으로 나온 횟수
1. 스택이 비어있으면 무조건 {n, 1}로 집어넣습니다.
2. 만약 stk의 맨 위랑 n이랑 같으면 {n, stk.back().cnt + 1}로 집어넣습니다.
3. 만약 stk의 맨 위랑 n이랑 다르면 맨 위에 있던 cnt값이 4보다 크거나 같은지 작은지 판단합니다.
    3.1 4보다 크거나 같으면 target을 위에서부터 다 뺍니다.
    3.2 아니면 그냥 {n, 1}로 집어넣습니다.
4. 마지막까지 같은 숫자일 수 있으므로 다시 3.1을 실행합니다.
*/

struct Info{
    int n, cnt;
};

int N;
int arrOrigin[MAX_N];
int result = MAX_N;

void simulation(vector<int> arr){
    vector<Info> stk;
    bool flag = false;

    for(int n : arr){
        if(stk.empty()){
            stk.push_back({n, 1});
        }
        else{
            if(stk.back().n == n){
                stk.push_back({n, stk.back().cnt + 1});
            }
            else{
                if(stk.back().cnt >= 4){
                    int target = stk.back().n;

                    while(!stk.empty() && stk.back().n == target){
                        stk.pop_back();
                    }

                    if(!stk.empty() && stk.back().n == n){
                        stk.push_back({n, stk.back().cnt + 1});
                    }
                    else{
                        stk.push_back({n, 1});
                    }
                }
                else{
                    stk.push_back({n, 1});
                }
            }
        }
    }
    if(!stk.empty() && stk.back().cnt >= 4){
        int target = stk.back().n;
    
        while(!stk.empty() && stk.back().n == target){
            stk.pop_back();
        }
    }

    result = min(result, (int)stk.size());
}

int get_next_same(int idx){
    int start = arrOrigin[idx+1];
    int cnt = 1;

    for(int i=idx+2; i<N; i++){
        if(start == arrOrigin[i]) cnt++;
        else break;

        if(cnt >= 3) return cnt;
    }

    return cnt;
}

int get_prev_same(int idx){
    int start = arrOrigin[idx-1];
    int cnt = 1;

    for(int i=idx-2; i>-1; i--){
        if(start == arrOrigin[i]) cnt++;
        else break;

        if(cnt >= 3) return cnt;
    }

    return cnt;
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N;
    vector<int> arr(N, 0);
    for(int i=0; i<N; i++){
        cin >> arrOrigin[i];
        arr[i] = arrOrigin[i];
    }

    result = N;
    int nextSame, prevSame;

    for(int i=0; i<N; i++){
        if(i != N-1) nextSame = get_next_same(i);
        if(i != 0) prevSame = get_prev_same(i);

        if(i == 0){
            if(nextSame >= 3){
                arr[i] = arr[i+1];
                simulation(arr);
            }
        }
        else if (i == N -1){
            if(prevSame >= 3){
                arr[i] = arr[i-1];
                simulation(arr);
            }
        }
        else{
            bool flag = true;
            if(nextSame >= 3){
                arr[i] = arr[i+1];
                simulation(arr);
                flag = false;
            }
            if(prevSame >= 3){
                arr[i] = arr[i-1];
                simulation(arr);
                flag = false;
            }

            if(flag && arr[i-1] == arr[i+1] && prevSame + nextSame >= 3){
                arr[i] = arr[i+1];
                simulation(arr);
            }
        }
        arr[i] = arrOrigin[i];
    }

    cout << result << '\n';

    return 0;
}