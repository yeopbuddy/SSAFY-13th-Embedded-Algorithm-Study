#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> MARS(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> MARS[i][j];
        }
    }
    // 맨 위 열은 도달하는 방법이 오른쪽으로 쭉 가는 것 밖에 없음 !! [0][1] 부터 [0][m]은 이전 값들 더하면서 setting
    vector<vector<int>> DPMAIN(n, vector<int>(m, 0));
    DPMAIN[0][0] = MARS[0][0];
    for(int i = 1; i < m; i++){
        DPMAIN[0][i] += DPMAIN[0][i-1] + MARS[0][i];
    }   
    // 다음 줄은 이제 .... 어케 하지...
    for(int i = 1; i < n; i++){
        vector<int> DPLEFT(m, 0); // 누적 최대 합 배열 생성
        vector<int> DPRIGHT(m, 0); // 누적 최대 합 배열 생성
        for(int j = 0; j < m; j++){
            if(j == 0){
                DPLEFT[j] = DPMAIN[i-1][j] + MARS[i][j];
                DPRIGHT[m-j-1] = DPMAIN[i-1][m-j-1] + MARS[i][m-j-1];
            }
            else{
                DPLEFT[j] = MARS[i][j] + max(DPLEFT[j-1], DPMAIN[i-1][j]);
                DPRIGHT[m-j-1] = MARS[i][m-j-1] + max(DPMAIN[i-1][m-j-1], DPRIGHT[m-j]);
            }
        }
        for(int j = 0; j < m; j++){
            DPMAIN[i][j] = max(DPLEFT[j], DPRIGHT[j]);
        }
    }   
    cout << DPMAIN[n-1][m-1];
}