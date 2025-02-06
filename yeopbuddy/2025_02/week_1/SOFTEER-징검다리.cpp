#include<iostream>
using namespace std;
int stoneBridge[3000] = {0};
int pdpd[3000] = {0};
int main(int argc, char** argv){
    int n, num;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> num;
        stoneBridge[i] = num;
        pdpd[i] = 1;
    }
    int bfmax;
    for(int i = 0; i < n; i++){
        bfmax = 0;
        for(int j = 0; j < i; j++){
            if(stoneBridge[j] < stoneBridge[i] && pdpd[j] > bfmax){
                bfmax = pdpd[j];
            }
        }
        pdpd[i] += bfmax;
    }
    int pdpdmax = pdpd[0];
    for(int i = 1; i < n; i++){
        if(pdpdmax < pdpd[i]){
            pdpdmax = pdpd[i];
        }
    }
    cout << pdpdmax;
}