// 5577번 RBY팡!
// 구현, 시뮬레이션
/*
접근 방법: 

*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int pang(vector<int>& arr, int idx, int color){
    int N = arr.size();
    arr[idx] = color;
    vector<pair<int, int>> PANG;
    int before_color = -1, cnt = 0;
    for (int i = N-1; i >= 0; --i){
        int ele = arr[i];
        if (ele != before_color){
            if (cnt >= 4){
                PANG.pop_back();
                if (PANG.empty()){
                    PANG.push_back({ele, 1});
                    before_color = ele;
                    cnt = 1;
                } else {
                    int c = PANG.back().first;
                    if (c == ele){
                        cnt = PANG.back().second + 1;
                        PANG.pop_back();
                        PANG.push_back({ele, cnt});
                        before_color = ele;
                    } else {
                        cnt = 1;
                        PANG.push_back({ele, cnt});
                        before_color = ele;
                    }
                }
            } else {
                cnt = 1;
                PANG.push_back({ele, cnt});
                before_color = ele;
            }
        } else {
            cnt++;
            if (PANG.empty()){
                PANG.push_back({ele, cnt});
            } else {
                PANG.pop_back();
                PANG.push_back({ele, cnt});
            }
        }
    }
    int ret = 0;
    for (auto p : PANG){
        if (p.second < 4) ret += p.second;
    }
    return ret;
}

int main(void){
    fastio;
    int N; cin >> N; // 공의 수
    vector<int> arr(N);
    for (int i = 0; i < N; ++i){
        cin >> arr[i];
    }
    int ans = N+1;
    for (int i = 0; i < N; ++i){
        int num = arr[i];
        int near1, near2;
        if (i != 0 && i != N-1){
            near1 = arr[i-1], near2 = arr[i+1];
            if (near1 == near2 && near1 == num){
                continue;
            } else if (near1 == near2 && near1 != num){
                ans = min(ans, pang(arr, i, near1));
                arr[i] = num;
            } else if (near1 == num){
                ans = min(ans, pang(arr, i, near2));
                arr[i] = num;
            } else if (near2 == num){
                ans = min(ans, pang(arr, i, near1));
                arr[i] = num;
            } else {
                ans = min(ans, pang(arr, i, near1));
                arr[i] = num;
                ans = min(ans, pang(arr, i, near2));
                arr[i] = num;
            }
        } else {
            if (i == 0){
                near1 = arr[i+1];
                if (near1 == num) continue;
                ans = min(ans, pang(arr, i, near1));
                arr[i] = num;
            } else {
                near1 = arr[i-1];
                if (near1 == num) continue;
                ans = min(ans, pang(arr, i, near1));
                arr[i] = num;
            }
        }
    }
    cout << ans;
    return 0;
}