#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> farm(n, vector<int>(m, 0));
    vector<pair<int, int>> coords;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int num; cin >> num;
            if(num == 1){
                farm[i][j] = 1;
                coords.push_back({i, j});
                cnt++;    
            }
        }
    }
    if(cnt == 2 * k){
        cout << "0";
    }else if(cnt == 2 * k - 1){ // 1개짜리 교차점 찾기
        cout << "1\n";
        if(cnt == 1){
            cout << coords[0].first + 1 << " " << coords[0].second + 1;
        }else{
            int x, y;
            bool findx = false;
            bool findy = false;
            for(int i = 0; i < coords.size(); i++){
                for(int j = i + 1; j < coords.size(); j++){
                    if(findx && findy){
                        break;
                    }else{
                        if(!findx && coords[i].first == coords[j].first){
                            x = coords[i].first;
                            findx = true;
                        }
                        if(!findy && coords[i].second == coords[j].second){
                            y = coords[i].second;
                            findy = true;
                        }
                    }   
                }
            }
            if(findx && findy){
                cout << x + 1 << " " << y + 1;    
            }else{
                cout << coords[coords.size() / 2].first + 1 << " " << coords[coords.size() / 2].second + 1;
            }
        }
    }else{ // 2개 이상 교차점 찾기
        cout << 2 * k - cnt << "\n";
        for(int i = cnt - k; i < k; i++){
            cout << coords[i].first + 1 << " " << coords[i].second + 1 << "\n";
        }
    }
}