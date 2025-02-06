#include<iostream>


using namespace std;

int main(int argc, char** argv){
    int n;
    cin >> n;
    int a,b;
    if(n == 1){
        cin >> a >> b;
        if(a < b){
            cout << a;
        }
        else{
            cout << b;
        }
    }
    else{
        int a2b,b2a;
        int beforea = 0;
        int beforeb = 0;
        for(int i = 0; i < n; i++){
            if(i != n - 1){
                cin >> a >> b >> a2b >> b2a;
                if(i != 0){
                    a += beforea;
                    b += beforeb;    
                }
                beforea = min(a, b + b2a);
                beforeb = min(b, a + a2b);    
                
            }
            else{
                cin >> a >> b;
                cout << min(beforea + a, beforeb + b);
            }
        }
    }
}