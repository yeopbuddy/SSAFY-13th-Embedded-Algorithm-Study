#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;

int main(){
    const int INF = 1e9;
    
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    int n, m;    
    cin >> n >> m;
    
    vector<vector<int>> MIN_D(n + 1, vector<int>(n + 1, INF));
    
    for(int i = 1; i < n + 1; i++){
        MIN_D[i][i] = 0;
    }
    
    for(int i = 0; i < m; i++){
        int u, v, b;
        cin >> u >> v >> b;
        if(b == 1){
            MIN_D[u][v] = 0;
            MIN_D[v][u] = 0;
        }
        else{
            MIN_D[u][v] = 0;
            MIN_D[v][u] = 1; // 비용 삐용 ㅋㅋ
        }
    }
    
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (MIN_D[i][j] > MIN_D[i][k] + MIN_D[k][j]) {
                    MIN_D[i][j] = MIN_D[i][k] + MIN_D[k][j];
                }
            }
        }
    }
    
    
    int k;
    cin >> k;
    for(int i = 0; i < k; i++){
        int u, v;
        cin >> u >> v;
        cout << MIN_D[u][v] << "\n";
    }
}