#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>
using namespace std;

int dirchange1(int dir, char mode){
    if(mode == '/'){
        if(dir == 0){
            return 1;
        }
        else if(dir == 1){
            return 0;
        }
        else if(dir == 2){
            return 3;
        }
        else{
            return 2;
        }
    }
    else{
        if(dir == 0){
            return 3;
        }
        else if(dir == 3){
            return 0;
        }
        else if(dir == 1){
            return 2;
        }
        else{
            return 1;
        }
    }
}
void dirprint(int dir){
    if(dir == 0){
        cout << "U\n";
    }
    else if(dir == 1){
        cout << "R\n";
    }
    else if(dir == 2){
        cout << "D\n";
    }
    else{
        cout << "L\n";
    }
}


int main(){
    int n, m, x, y;
    cin >> n >> m;
    
    vector<vector<char>> SPACESPACE(n, vector<char>(m));
    
    vector<vector<string>> PATH(n, vector<string>(m, ""));
    
    bool visit[501][501];
    
    map<int, pair<int, int>> NUM2DIR;
    NUM2DIR[0] = {-1, 0}; NUM2DIR[1] = {0, 1}; NUM2DIR[2] = {1, 0}; NUM2DIR[3] = {0, -1};
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> SPACESPACE[i][j];
        }
    }
    
    cin >> x >> y; x--; y--;
    
    int ans = 0;
    int cnt = 0;
    int fdir = 0;
    for(int i = 0; i < 4; i++){
        memset(visit, false, sizeof(visit)); // memset을 통해 visit 배열을 false로 초기화해준다.
        int dir = i;
        PATH[x][y] += to_string(dir); // 시작 좌표와 시작 방향(0 : 위, 1 : 오른쪽, 2 : 아래, 3 : 왼쪽)을 PATH에 넣는다
        if(SPACESPACE[x][y] == 'C'){ // 시작 좌표가 블랙홀일 경우 : 반복을 종료한다.
            continue;
        }
        // 시작 좌표가 / 혹은 \인 경우 : 바뀐 방향에 대서도 PATH에 넣는다. 그리고 방향을 바꾼다.
        else if(SPACESPACE[x][y] == '/' || SPACESPACE[x][y] == '\\'){ // 0 -> 1, 1 -> 0, 2-> 3, 3 -> 2
            dir = dirchange1(dir, SPACESPACE[x][y]);
            PATH[x][y] += to_string(dir);
        }
        int cx = x; int cy = y;
        visit[cx][cy] = true; 
        while(true){ // 설정된 방향에 대해 WHILE문을 통해 탐색을 시작한다 : while문 내부에서는 다음과 같은 동작을 수행한다.
            cnt++; // cnt를 1 증가시키며 정해진 방향 dir에 대해서 정해진 방향으로 탐색 (cx += NUM2DIR[dir].first, cy += NUM2DIR[dir].second)을 수행한다.
            cx += NUM2DIR[dir].first;
            cy += NUM2DIR[dir].second;
            if(0 <= cx && cx < n && 0 <= cy && cy < m && SPACESPACE[cx][cy] != 'C'){
                if(visit[cx][cy]){ // visit[CX][CY]가 TRUE인 경우, PATH[CX][CY]의 요소들랑 현재 방향이랑 겹치는지 확인한다.
                    for(int j = 0; j < PATH[cx][cy].size(); j++){
                        if(PATH[cx][cy][j] - '0' == dir){ // 겹칠 경우, 무한루프이므로 dir을 업데이트하고 반복을 종료한다.
                            dirprint(dir);
                            cout << "Voyager";
                            return 0;
                        }
                    }
                    PATH[cx][cy] += to_string(dir);
                }
                // 해당 좌표 cx, cy가 / 또는 \인 경우 : 마찬가지로 방문에 대한 조건 확인 및 무한루프 조건을 확인해준다 : 이때, 현재 방향과 바뀔 방향에 대해 모두 check한다.
                if(SPACESPACE[cx][cy] == '/' || SPACESPACE[cx][cy] == '\\'){ 
                    dir = dirchange1(dir, SPACESPACE[cx][cy]);
                    PATH[cx][cy] += to_string(dir); // 무한루프에 해당하지 않으면, 현재 이동 방향과 바뀐 이동 방향 모두를 PATH[CX][CY]에 추가한다.
                }
                visit[cx][cy] = true;
            }
            else{ // 해당 좌표 cx, cy가 범위를 벗어났거나 블랙홀인 경우 : 종료 조건
                if(ans < cnt){ // cnt가 ans보다 크면 dir과 ans를 업데이트해준다.(크거나 같음 X, 클 경우만)
                    fdir = i;
                    ans = cnt;
                }
                for(int j = 0; j < n; j++){ // 반복이 끝나면, PATH vector를 ""로 초기화해준다.
                    for(int k = 0; k < m; k++){
                        PATH[j][k] = "";
                    }
                }
                cnt = 0;
                break;
            }
        }
    }
    dirprint(fdir);
    cout << ans;
    
    return 0;
}