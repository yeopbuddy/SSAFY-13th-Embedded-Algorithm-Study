#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> DP;
int n, m, k; 
bool CanReachLose(int x, int y){ // 아래, 오른쪽, 대각선 우하단 check
    // down
    if(x + 1 < n && DP[x+1][y] == 2){
        return true;
    }
    // right
    if(y + 1 < m && DP[x][y+1] == 2){
        return true;
    }
    // dg
    int cp_k = k;
    x++; y++;
    while(x < n && y < m && cp_k > 0){
        if(DP[x][y] == 2){
            return true;
        }
        x++; y++; cp_k--;
    }
    return false; // 어디에도 후공이 이기는 경우 DP[x'][y'] = 2가 없으면 패배!
}

int main(){
    cin >> n >> m >> k;
    DP.resize(n, vector<int>(m, 0));
    DP[n-1][m-1] = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char c; cin >> c;
            if(c == '#'){
                DP[i][j] = -1;
            }
        }
    }
    
    // 아래와 오른쪽, 도착지 기준 대각선 먼저 채움
    bool fstwin = true;
    for(int i = m - 2; i >= 0; i--){ // 아래 채우기
        if(DP[n-1][i] != -1){
            if(fstwin){
                DP[n-1][i] = 1;
                fstwin = false;
            }
            else{
                DP[n-1][i] = 2;
                fstwin = true;
            }
        }
        else{
            break;
        }
    }
    fstwin = true;
    for(int i = n - 2; i >= 0; i--){ // 오른쪽 채우기
        if(DP[i][m-1] != -1){
            if(fstwin){
                DP[i][m-1] = 1;
                fstwin = false;
            }
            else{
                DP[i][m-1] = 2;
                fstwin = true;
            }
        }
        else{
            break;
        }
    }
    int dgx = n - 2; int dgy = m - 2; int cpk = k;
    while(dgx >= 0 && dgy >= 0 && cpk > 0){ // 도착지 기준 대각선 좌상단 채우기
        if(DP[dgx][dgy] == 0){
            DP[dgx][dgy] = 1;
        }
        dgx--; dgy--; cpk--;
    }
    
    // 초기값 세팅 후 DP VECTOR 채우기
    for(int i = n - 2; i >= 0; i--){
        for(int j = m - 2; j >= 0; j--){
            if(DP[i][j] == 0){
                if(CanReachLose(i, j)){
                    DP[i][j] = 1;
                }
                else{
                    DP[i][j] = 2;
                }   
            }
        }
    }

    int tc; cin >> tc;
    for(int i = 0; i < tc; i++){
        int x, y; cin >> x >> y;
        if(DP[--x][--y] == 1){
            cout << "First\n";
        }
        else{
            cout << "Second\n";
        }
    }
    return 0;
}