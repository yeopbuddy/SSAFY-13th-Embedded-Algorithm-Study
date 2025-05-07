#include <iostream>
using namespace std;
int schedules[365];
int main(){
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int s, e; cin >> s >> e;
        for(int j = s; j <= e; j++){
            schedules[j - 1]++;
        }
    }
    
    int d = 0;
    int h, w;
    bool iscont = false;
    int ans = 0;
    while(d < 365){
        if(schedules[d] != 0){
            if(iscont){
                if(h < schedules[d]){
                    h = schedules[d];
                }
                w++;
                if(d == 364){
                    ans += h * w;   
                }
            }
            else{
                iscont = true;
                h = schedules[d];
                w = 1;
                if(d == 364){
                    ans += h * w;   
                }
            }
        }
        else{
            if(iscont){
                ans += h * w;   
                iscont = false;
                h = 0;
                w = 0;
            }
        }
        d++;
    }
    cout << ans;
    return 0;
}