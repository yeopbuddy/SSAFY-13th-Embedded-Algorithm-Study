// 12869번 뮤탈리스크
// bfs
/*
접근 방법:
bfs
*/
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    int N; cin >> N;
    if (N == 1){
        int A; cin >> A;
        cout << (A-1)/9 + 1 << endl;
        return 0;
    }
    vector<vector<int>> minus2 = {{9, 3}, {3, 9}};
    vector<vector<int>> minus3 = {{9, 3, 1}, {9, 1, 3}, {3, 9, 1}, {3, 1, 9}, {1, 9, 3}, {1, 3, 9}};
    if (N == 2){
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        map<vector<int>, int> VIS;
        VIS[A] = 0;
        queue<pair<vector<int>, int>> Q;
        Q.push({A, 0});
        vector<int> target(N, 0);
        while (!Q.empty()){
            vector<int> a = Q.front().first;
            int time = Q.front().second;
            Q.pop();
            if (a == target){
                cout << time << endl;
                return 0;
            }
            for (int i = 0; i < minus2.size(); i++){
                vector<int> new_a;
                for (int j = 0; j < N; j++){
                    new_a.push_back(max(0, a[j]-minus2[i][j]));
                }
                if (VIS.find(new_a) == VIS.end()){
                    VIS[new_a] = time+1;
                    Q.push({new_a, time+1});
                }
            }
        }
    }
    else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        map<vector<int>, int> VIS;
        VIS[A] = 0;
        queue<pair<vector<int>, int>> Q;
        Q.push({A, 0});
        vector<int> target(N, 0);
        while (!Q.empty()){
            vector<int> a = Q.front().first;
            int time = Q.front().second;
            Q.pop();
            if (a == target){
                cout << time << endl;
                return 0;
            }
            for (int i = 0; i < minus3.size(); i++){
                vector<int> new_a;
                for (int j = 0; j < N; j++){
                    new_a.push_back(max(0, a[j]-minus3[i][j]));
                }
                if (VIS.find(new_a) == VIS.end()){
                    VIS[new_a] = time+1;
                    Q.push({new_a, time+1});
                }
            }
        }
    }
    return 0;
}