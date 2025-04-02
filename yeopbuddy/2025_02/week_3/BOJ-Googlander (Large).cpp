#include <iostream>
using namespace std;
long long memo[25][25];

int main(){
    for(int i = 0; i < 25; i++){
        memo[0][i] = 1;
        memo[i][0] = 1;
    }
    for(int i = 1; i < 25; i++){
        for(int j = 1; j < 25; j++){
            memo[i][j] = memo[i-1][j] + memo[i][j-1];
        }
    }
    int tc;
    cin >> tc;
    for(int i = 1; i <= tc; i++){
        int x, y;
        cin >> x >> y;
        cout << "Case #" << i << ": " << memo[x-1][y-1] << "\n";
    }
}