#include <iostream>
using namespace std;
long long DP[10001];

int main(){
    int N, M; 
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        DP[i] = 1;
    }
    for(int i = M; i <= 10000; i++){
        DP[i] = ((DP[i - 1]%1000000007) + (DP[i - M]%1000000007))%1000000007;
    }
    cout << DP[N];
    return 0;
}