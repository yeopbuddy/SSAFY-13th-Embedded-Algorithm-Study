#include <iostream>
#include <cstring>
#include <tuple>
#include <queue>
using namespace std;

int main(){
    int n;
    int arr[3] = {0};
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int scv1 = arr[0];
    int scv2 = arr[1];
    int scv3 = arr[2];
    int attacklist[6][3] = {{1,3,9},{1,9,3},{3,1,9},{3,9,1},{9,1,3},{9,3,1}};
    
    queue<tuple<int, int, int, int>> q; // scv1, scv2, scv3, attack trial
    bool visited[61][61][61];
    memset(visited, false, sizeof(visited));
    q.push(make_tuple(scv1, scv2, scv3, 0));
    while(true){
        int c_scv1 = get<0>(q.front());
        int c_scv2 = get<1>(q.front());
        int c_scv3 = get<2>(q.front());
        int trial = get<3>(q.front());
        // cout << c_scv1 << " " << c_scv2 << " " << c_scv3 << " " << trial << "\n";
        if(c_scv1 <= 0 && c_scv2 <= 0 && c_scv3 <= 0){
            cout << trial;
            break;
        }
        q.pop();
        for(int i = 0; i < 6; i++){
            int new_scv1 = c_scv1 - attacklist[i][0];
            int new_scv2 = c_scv2 - attacklist[i][1];
            int new_scv3 = c_scv3 - attacklist[i][2];
            if(new_scv1 < 0){
                new_scv1 = 0;
            }
            if(new_scv2 < 0){
                new_scv2 = 0;
            }
            if(new_scv3 < 0){
                new_scv3 = 0;
            }
            if(!visited[new_scv1][new_scv2][new_scv3]){
                visited[new_scv1][new_scv2][new_scv3] = true;
                q.push(make_tuple(new_scv1, new_scv2, new_scv3, trial + 1));   
            }
        }
    }

    return 0;
}