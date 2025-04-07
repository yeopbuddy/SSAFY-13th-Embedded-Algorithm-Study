#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        int n; cin >> n;
        vector<int> Cards(n);
        vector<int> SumStack(n + 1, 0);
        for(int j = 0; j < n; j++){
            cin >> Cards[j];
            SumStack[j + 1] = SumStack[j] + Cards[j];
        }
        int distance = 1;
        while(distance != n){
            vector<int> DP(n - distance);
            int st = 1; int ed = st + distance;
            while(ed <= n){
                DP[st - 1] = (SumStack[ed] - SumStack[st - 1]) - min(Cards[st - 1], Cards[st]);
                st++; ed++;
            }
            for(int i = 0; i < n-distance; i++){
                Cards[i] = DP[i];
            }
            distance++;
        }
        cout << Cards[0] << "\n";
    }

    return 0;
}