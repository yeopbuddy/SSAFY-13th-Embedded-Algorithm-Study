#include <iostream>
#include <vector>
using namespace std;
// DP[i][j] = plumtree[j] + max(DP[i - 1][j - 1], DP[i][j - 2]);
int main(){
    int t, w;
    cin >> t >> w; w++;
    vector<int> plumtree;
    int prev_plumno; cin >> prev_plumno;
    int plumcnt = 1;
    if(prev_plumno == 2){
        plumtree.push_back(0);
    }
    for(int i = 1; i < t; i++){
        int plum_no; cin >> plum_no;
        if(prev_plumno == plum_no){
            plumcnt++;
        }
        else{
            plumtree.push_back(plumcnt);
            prev_plumno = plum_no;
            plumcnt = 1;
        }
    }
    plumtree.push_back(plumcnt);
    
    size_t VECTORLEN = plumtree.size();
    vector<vector<int>> DP(w, vector<int>(VECTORLEN, 0));
    int ans = 0;
    
    for(int i = 0; i < VECTORLEN; i++){ // 1층 먼저 쌓기
        if(i % 2 == 0){
            DP[0][i] = plumtree[i];
        }
        else{
            DP[0][i] = 0;
        }
    }
    for(int i = 1; i < w; i++){
        for(int j = 0; j < VECTORLEN; j++){
            int DPVAL1 = 0; int DPVAL2 = 0;
            if(0 <= j - 1){
                DPVAL1 = DP[i - 1][j - 1];
            }
            if(j - 2 >= 0){
                DPVAL2 = DP[i][j - 2];
            }
            DP[i][j] = plumtree[j] + max(DPVAL1, DPVAL2);
            if(ans < DP[i][j]){
                ans = DP[i][j];
            }
        }
    }
    cout << ans;
    return 0;
}