#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int n; cin >> n;
    vector<pair<int, int>> ELINE(n);
    for(int i = 0; i < n; i++){
        cin >> ELINE[i].first >> ELINE[i].second;
    }
    sort(ELINE.begin(), ELINE.end()); // 명시 없으면 알아서 first 기준으로 sort ! 
    // 새로 pair 아닌 1차원 배열 만들어서 향하는 전깃줄 값만 빼서 저장할까 하다가 .. 그냥 해야것다
    vector<int> LIS(n, 1);
    for(int i = 0; i < n; i++){
        int mxv = 0;
        for(int j = 0; j < i; j++){
            if(ELINE[i].second > ELINE[j].second && mxv < LIS[j]){
                mxv = LIS[j];
            }
        }
        LIS[i] += mxv;
    }
    int rmxv = 0;
    for(int i = 0; i < n; i++){
        // cout << LIS[i] << " ";
        if(LIS[i] > rmxv){
            rmxv = LIS[i];
        }
    }
    // cout << "\n";
    cout << n - rmxv;
}