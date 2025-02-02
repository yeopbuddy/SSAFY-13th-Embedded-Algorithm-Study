#include<iostream>


using namespace std;

int main(int argc, char** argv){
    int N;
    cin >> N;
    int result = 0;
    for(int i=0; i<N; i++){
        int p, c;
        cin >> p >> c;
        if(abs(p-result) <= c){
            result += 1;
        }
    }

    cout << result << '\n';

   return 0;
}