#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int DROP7[7][7];

int SIMULATE_DROP7(int col, int ball){
    // copy array + drop the ball 
    int val = 0;
    int arr[7][7];
    bool notplaced = true;
    for(int i = 6; i >= 0; i--){
        for(int j = 6; j >= 0; j--){
            arr[i][j] = DROP7[i][j];
            if(col == j && arr[i][j] == 0 && notplaced){
                notplaced = false;
                arr[i][j] = ball;    
            }
        }
    }
    
    // Iterate start.
    while(true){
        // find the row/col group
        vector<vector<vector<int>>> group;
        vector<vector<int>> row_sub;
        vector<vector<int>> col_sub;
        
        for(int i = 0; i < 7; i++){ // row -> group
            // bool continues = false;
            for(int j = 0; j < 7; j++){
                if(arr[i][j] != 0){
                    row_sub.push_back({arr[i][j], i, j});
                    if(j == 6){
                        group.push_back(row_sub);
                        row_sub.clear();
                    }
                }
                else{ // 0
                    if(row_sub.size() > 0){
                        group.push_back(row_sub);
                    }
                    row_sub.clear();
                }
            }
        }
        
        for(int i = 0; i < 7; i++){ // col -> group
            bool continues = false;
            for(int j = 0; j < 7; j++){
                if(arr[j][i] != 0){
                    col_sub.push_back({arr[j][i], j, i});
                    if(j == 6){
                        group.push_back(col_sub);
                        col_sub.clear();
                    }
                }
                else{ // 0
                    if(col_sub.size() > 0){
                        group.push_back(col_sub);   
                    }
                    col_sub.clear();
                }
            }
        }
        
        bool deletelist[7][7];
        memset(deletelist, false, sizeof(deletelist));
        int deletecnt = 0;
        for(int i = 0; i < group.size(); i++){
            int grs = group[i].size();
            for(int j = 0; j < group[i].size(); j++){
                for(int k = 0; k < group[i][j].size(); k++){
                    if(k % 3 == 0 && group[i][j][k] == grs){
                        deletelist[group[i][j][k+1]][group[i][j][k+2]] = true;
                        deletecnt++;
                    }
                }
            }
            // cout << "\n";
        }
        if (deletecnt == 0){
            break;   
        }
        else{ // delete + pull down
            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 7; j++){
                    if(deletelist[i][j]){
                        val++;
                        arr[i][j] = 0;   
                    }
                }
            }
            // hey gravity..
            for(int i = 0; i < 7; i++){
                vector<int> vec;
                for(int j = 0; j < 7; j++){
                    if(arr[j][i] != 0){
                        vec.push_back(arr[j][i]);
                    }
                }
                for(int j = 0; j < 7 - vec.size(); j++){
                    arr[j][i] = 0;
                }
                int vecidx = 0;
                for(int j = 7 - vec.size(); j < 7; j++){
                    arr[j][i] = vec[vecidx];
                    vecidx++;
                }
                vec.clear();
            }
        }
    }
    return val;
}

int main(){
    int bc = 1;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            cin >> DROP7[i][j];
            if(DROP7[i][j] != 0){
                bc++;
            }
        }
    }
    int n; cin >> n;
    int max_ball = 0;
    for(int i = 0; i < 7; i++){
        int res = SIMULATE_DROP7(i, n);
        if(res > max_ball){
            max_ball = res;
        }
    }
    
    cout << bc - max_ball;
}