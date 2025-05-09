#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n; cin >> n;
    vector<int> latency(n + 1);
    vector<vector<int>> dependancy(n + 1);
    for(int i = 1; i <= n; i++){
        int a; cin >> latency[i] >> a;
        vector<int> sub;
        for(int j = 0; j < a; j++){
            int b; cin >> b;
            sub.push_back(b);
        }
        dependancy[i] = sub;
    }
    
    int ans = latency[0];
    
    for(int i = 2; i <= n; i++){ // 1번 작업은 선행 작업 없으므로 2부터 시작
        int mxt = 0;
        for(int d : dependancy[i]){
            mxt = max(mxt, latency[d]);
        }
        latency[i] += mxt;
        ans = max(ans, latency[i]);
    }
    
    cout << ans;
    
    return 0;
}