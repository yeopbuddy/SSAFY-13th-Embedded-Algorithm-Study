#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

/*
누가봐도 dp 문제입니다.
dp 테이블을 정의해봅시다.
dp[j][i] : i초가 지났을 때, j번을 이동해서 자두를 받을 수 있는 최댓값.

현재까지 i초가 지났고
1. a가 2일 때
    1.1. j % 2 == 1 이면, 그냥 제자리에 있어도 받을 수 있습니다. 개꿀띠
                    그냥 있거나 남아있는 W를 하나 쓰고 움직입니다.
                    dp[j][i] = max(dp[j][i-1], dp[j-1][i-1]) + 1;

    1.2. j % 2 == 0 이면, 그냥 있거나 위에서 계산된 값의 최댓갑
                    dp[j][i] = max(dp[j-1][i], dp[j][i-1]);

2. a가 1일 때
    2.1. j % 2 == 0 이면, 그냥 제자리에 있어도 받을 수 있습니다. 개꿀띠띠
                    그냥 있거나 남아있는 W를 하나 쓰고 움직입니다.  
                    dp[j][i] = max(dp[j][i-1], dp[j-1][i-1]) + 1;
    
    2.2. j % 2 == 1 이면, 그냥 있거나 위에서 계산된 값의 최댓갑
                    dp[j][i] = max(dp[j-1][i], dp[j][i-1]);

이렇게 하면 dp[W][T]에 최댓값이 담기게 됩니다.
*/


#define MAX_T 1000
#define MAX_W 30

int T, W;
int dp[MAX_W+1][MAX_T+1];

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> T >> W;
    int a;
    for(int i=1; i<=T; i++){
        cin >> a;
        for(int j=0; j<=W; j++){
            if(a == 2){
                if(j%2 == 0){
                    if(j == 0){
                        dp[j][i] = dp[j][i-1];
                    }
                    else{
                        dp[j][i] = max(dp[j-1][i], dp[j][i-1]);
                    }
                }
                else{
                    dp[j][i] = max(dp[j][i-1], dp[j-1][i-1]) + 1;
                }
            }
            else{
                if(j%2 == 0){
                    if(j == 0){
                        dp[j][i] = dp[j][i-1] + 1;
                    }
                    else{
                        dp[j][i] = max(dp[j][i-1], dp[j-1][i-1]) + 1;
                    }
                }
                else{
                    dp[j][i] = max(dp[j-1][i], dp[j][i-1]);
                }
            }
        }

    }


    // for(int i=0; i<=W; i++){
    //     for(int j=0; j<=T; j++){
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << dp[W][T] << '\n';


    return 0;
}