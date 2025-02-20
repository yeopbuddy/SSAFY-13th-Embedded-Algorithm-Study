#include<iostream>
#include<cmath>
using namespace std;

int main(int argc, char** argv){
    int n, p, c;
    int my = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> p >> c;
        if(abs(my-p) <= c){
            my++;
        }
    }
    cout << my;
    return 0;
}