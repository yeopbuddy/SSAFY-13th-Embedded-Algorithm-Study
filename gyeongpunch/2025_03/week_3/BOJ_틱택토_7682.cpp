#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

#define SZ 3

/*
if(xCnt-oCnt < 0 || 1 < xCnt-oCnt){
    result = "invalid";
}
위에 있는 가지치기 때문에 같은 돌이 동시에 빙고일 경우가 없군요! 리발ㅎ

xCnt, X: X돌 개수
oCnt, O: O돌 개수

1. 끝났을 때 xCnt-oCnt가 0 또는 1이 아니면 아묻따 invalid입니다.
2. Bingo 구조체에 X와 O이 빙고인지 아닌지를 저장합니다.
3. X, O 둘 다 동시에 빙고면 invalid입니다.
4. 둘 다 빙고가 아닐 때, X+O != 9면 invalid입니다.
5. X만 빙고일 때는 X != O+1 면 invalid입니다.
6. O만 빙고일 때는 X != O 면 invalid입니다.
7. 위에의 가지치기에서 살아남았다면 당신은 valid입니다. 축하합니다.
*/

struct Bingo{
    int xB, oB;
};

char arr[SZ][SZ];
Bingo bingo;

void get_bingo(){
    bingo.xB = bingo.oB = 0;

    for(int i=0; i<SZ; i++){
        if('X' == arr[i][0] && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) bingo.xB = 1;
        if('X' == arr[0][i] && arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) bingo.xB = 1;
        
        if('O' == arr[i][0] && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) bingo.oB = 1;
        if('O' == arr[0][i] && arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) bingo.oB = 1;
    }

    if('X' == arr[0][0] && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) bingo.xB = 1;
    if('X' == arr[0][2] && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) bingo.xB = 1;
    
    if('O' == arr[0][0] && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) bingo.oB = 1;
    if('O' == arr[0][2] && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) bingo.oB = 1;
}

string get_result(const int &X, const int &O){
    get_bingo();
    
    if(bingo.xB > 0 && bingo.oB > 0) return "invalid";
    
    else if(bingo.xB == 0 && bingo.oB == 0) {
        if(X+O != 9) return "invalid";
    }
    else {
        if(bingo.xB > 0 && X != O + 1) return "invalid"; 
        else if (bingo.oB > 0 && X != O) return "invalid";
    }
    return "valid";
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    string b, result;
    int xCnt, oCnt;
    while(true){
        cin >> b;

        if(b == "end"){
            break;
        }
        
        xCnt = 0;
        oCnt = 0;
        for(int i=0; i<SZ; i++){
            for(int j=0; j<SZ; j++){
                arr[i][j] = b[i*SZ + j];

                if(arr[i][j] == 'X') xCnt++;
                else if(arr[i][j] == 'O') oCnt++;
            }
        }

        if(xCnt-oCnt < 0 || 1 < xCnt-oCnt){
            result = "invalid";
        }
        else{
            result = get_result(xCnt, oCnt);
        }
        cout << result << '\n';
    }

    return 0;
}