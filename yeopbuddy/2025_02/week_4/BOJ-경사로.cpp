#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n, l;
    cin >> n >> l;
    vector<vector<int>> vecmap (n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> vecmap[i][j];
        }
    }
    int ans = 0;
    // 이중 반복 한번에 horizontal, vertical 모두 연산하려 했는데 변수 꼬여서 그냥 두번 씀 ..
    // get possible horizontal
    for(int i = 0; i < n; i++){
        bool possible = true;
        int ramp = -1;
        for(int j = 1; j < n; j++){
            int temp = vecmap[i][j];
            int befo = vecmap[i][j-1];
            if (!possible){
                break;
            }
            if(temp != befo){
                if(befo + 1 == temp && ramp < j - l){ // place ramp before
                    ramp = j - 1;
                }
                else if(befo - 1 == temp && ramp < j && j + l <= n){ // place ramp after
                    for(int k = j + 1; k < j + l; k++){
                        if(temp != vecmap[i][k]){
                            possible = false;
                            break;
                        }
                    }
                    if(possible){
                        ramp = j + l - 1;
                    }
                }
                else{
                    possible = false;
                    break;
                }
            }
        }
        if(possible){
            ans++;
        }
    }
    // get possible vertical
    for(int i = 0; i < n; i++){
        bool possible = true;
        int ramp = -1;
        for(int j = 1; j < n; j++){
            int temp = vecmap[j][i];
            int befo = vecmap[j-1][i];
            if (!possible){
                break;
            }
            if(temp != befo){
                if(befo + 1 == temp && ramp < j - l){ // place ramp before
                    ramp = j - 1;
                }
                else if(befo - 1 == temp && ramp < j && j + l <= n){ // place ramp after
                    for(int k = j + 1; k < j + l; k++){
                        if(temp != vecmap[k][i]){
                            possible = false;
                            break;
                        }
                    }
                    if(possible){
                        ramp = j + l - 1;
                    }
                }
                else{
                    possible = false;
                    break;
                }
            }
        }
        if(possible){
            ans++;
        }
    }
    cout << ans;
}