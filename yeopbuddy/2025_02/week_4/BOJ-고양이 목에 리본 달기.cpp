#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n, k;
    cin >> n >> k;
    // 고 양 이 조 아
    vector<int> CAT_IS_LOVELY(k, 0);
    vector<int> CAT_IS_CUTE(k, 0);
    int mx1idx = 0; int mx1val = 0; int mx2idx = 0; int mx2val = 0; int num;
    for(int j = 0; j < k; j++){
        cin >> num;
        CAT_IS_LOVELY[j] = num;
        if(num > mx1val){
            mx1idx = j;
            mx1val = num;
        }
    }
    for(int j = 0; j < k; j++){
        if(CAT_IS_LOVELY[j] > mx2val && j != mx1idx){
            mx2idx = j;
            mx2val = CAT_IS_LOVELY[j];
        }
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < k; j++){
            cin >> CAT_IS_CUTE[j];
        }
        for(int j = 0; j < k; j++){
            if(j == mx1idx){
                CAT_IS_CUTE[j] += mx2val;
            }
            else{
                CAT_IS_CUTE[j] += mx1val;
            }
        }
        mx1idx = 0; mx1val = 0; mx2idx = 0; mx2val = 0;
        for(int j = 0; j < k; j++){
            CAT_IS_LOVELY[j] = CAT_IS_CUTE[j];
            if(CAT_IS_LOVELY[j] > mx1val){
                mx1val = CAT_IS_LOVELY[j];
                mx1idx = j;
            }
        }
        for(int j = 0; j < k; j++){
            if(CAT_IS_LOVELY[j] > mx2val && j != mx1idx){
                mx2val = CAT_IS_LOVELY[j];
                mx2idx = j;
            }
        }
    }
    cout << mx1val;
}
