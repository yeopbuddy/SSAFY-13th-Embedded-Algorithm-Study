#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    bool isprime[1000001] = {true};
    fill(isprime, isprime + 1000001, true); // or cstring::memset ? 
    isprime[0] = false;
    isprime[1] = false;
    int n1, n2;
    cin >> n1 >> n2;
    for(int i = 2; i <= n2; i++){
        if(isprime[i]){
            for(int j = 2 * i; j <= n2; j += i){
                isprime[j] = false;
            }      
        }
    }
    for(int i = n1; i <= n2; i++){
        if(isprime[i]){
            cout << i << "\n";
        }
    }
}