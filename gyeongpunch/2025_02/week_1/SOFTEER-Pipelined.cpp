#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
    int N, result, mx=0;
    cin >> N;
    for(int i=0; i<N; i++){
        int task;
        cin >> task;
        mx = max(mx, task);
    }
    result = mx + N - 1;

    cout << result << '\n';
    
    return 0;
}