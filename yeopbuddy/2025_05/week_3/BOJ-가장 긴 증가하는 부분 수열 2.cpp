#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> seq(n);
    for(int i = 0; i < n; i++){
        cin >> seq[i];
    }
    vector<int> LIS = {seq[0]};
    for(int i = 1; i < n; i++){
        int lp = 0;
        int rp = LIS.size() - 1;
        int mid;
        if(LIS[rp] < seq[i]){
            LIS.push_back(seq[i]);
        }
        else{
            while(lp < rp){
                mid = (lp + rp) / 2;
                if(LIS[mid] < seq[i]){
                    lp = mid + 1;
                }else{
                    rp = mid;
                }
            }
            LIS[rp] = min(LIS[rp], seq[i]);
        }
        // for(int l : LIS){
        //     cout << l << " ";
        // }
        // cout << "\n";
    }
    cout << LIS.size() << "\n";
    
    
    return 0;
}