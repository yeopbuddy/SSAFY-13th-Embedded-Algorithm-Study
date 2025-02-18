#include <iostream>
using namespace std;
int stair[300] = {0};
int C[300] = {0};
int N[300] = {0};
int main(){
    int n, num;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> stair[i];
        if(i == 0){
            C[i] = stair[i];
            N[i] = 0;
        }
        else if (i == 1){
            C[i] = stair[i];
            N[i] = stair[i] + stair[i - 1];
        }
        else if (i == 2){
            C[i] = stair[i] + C[i-2];
            N[i] = stair[i] + stair[i - 1];
        }
        else{
            if(C[i-2] > N[i-2]){
                C[i] = stair[i] + C[i-2];
            }
            else{
                C[i] = stair[i] + N[i-2];
            }
            if(C[i-3] > N[i-3]){
                N[i] = stair[i] + stair[i - 1] + C[i - 3];
            }
            else{
                N[i] = stair[i] + stair[i - 1] + N[i - 3];
            }
        }
    }
    if(C[n-1] > N[n-1]){
        cout << C[n-1];
    }
    else{
        cout << N[n-1];
    }
    return 0;
}