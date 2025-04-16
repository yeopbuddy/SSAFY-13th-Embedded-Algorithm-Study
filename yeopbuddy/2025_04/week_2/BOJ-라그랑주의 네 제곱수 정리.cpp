#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main(){
    // DP[i] = 숫자 i를 4개 이하의 양의 제곱수의 합으로 만들 수 있는 경우의 수
    int DP[32768] = {0};
    int number = 1;
    vector<int> pownums;
    while(true){
        int cnum = number * number;
        if (cnum < 32768){
            DP[cnum] = 1;
            pownums.push_back(cnum);
        }
        else{
            break;
        }
        number++;
    }
    int siz = pownums.size();
    // 1개 조합은 이미 구함. 이제 2~4개 조합 구하면 되는둣
    
    // 2개 조합
    for(int i = 0; i < siz; i++){
        for(int j = i; j < siz; j++){
            int cnum = pownums[i] + pownums[j];
            if (cnum < 32768){
                DP[cnum]++;
            }
        }
    }
    // 3개 조합
    for(int i = 0; i < siz; i++){
        for(int j = i; j < siz; j++){
            for(int k = j; k < siz; k++){
                int cnum = pownums[i] + pownums[j] + pownums[k];    
                if (cnum < 32768){
                    DP[cnum]++;
                }
            }
        }
    }
    // 4개 조합
    for(int i = 0; i < siz; i++){
        for(int j = i; j < siz; j++){
            for(int k = j; k < siz; k++){
                for(int l = k; l < siz; l++){
                    int cnum = pownums[i] + pownums[j] + pownums[k] + pownums[l];    
                    if (cnum < 32768){
                        DP[cnum]++;
                    }   
                }
            }
        }
    }
    while(true){
        int cnum; 
        cin >> cnum;
        if(cnum == 0){
            break;
        }
        cout << DP[cnum] << "\n";
        
    }
    return 0;
}