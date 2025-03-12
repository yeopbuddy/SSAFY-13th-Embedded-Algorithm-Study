// 25331번 Drop 7
// 구현
/*
접근 방법:

*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

void findDelPos(const vector<vector<int>>& MAP, vector<pair<int, int>>& delPos){
    // 현재 상황은 항상 중력으로 인해 모두 아래로 내려가있는 상황이다.
    // 가장 아래줄부터, 왼쪽에서 오른쪽으로 살펴보며 연속된 그룹을 살펴본다.
    // 즉, 가로줄을 보자.
    for (int row = 6; row >= 0; row--){
        int groupSize = 0, groupStartIdx = 0;
        for (int col = 0; col < 7; col++){
            if (MAP[row][col] == 0){
                for (int i = groupStartIdx; i < col; i++){
                    if (MAP[row][i] == groupSize){
                        delPos.push_back({row, i});
                    }
                }
                groupSize = 0;
                groupStartIdx = col+1;
            }
            else{
                groupSize++;
            }   
        }
        if (groupSize != 0){
            for (int i = groupStartIdx; i < 7; i++){
                if (MAP[row][i] == groupSize){
                    delPos.push_back({row, i});
                }
            }
        }
    }
    // 이제 세로줄을 보자. 탐색 방향은 아래에서 위로 본다.
    for (int col = 0; col < 7; col++){
        int groupSize = 0;
        for (int row = 6; row >= 0; row--){
            if (MAP[row][col] == 0){
                for (int i = 6; i > row; i--){
                    if (MAP[i][col] == groupSize){
                        delPos.push_back({i, col});
                    }
                }
                break;
            }
            else groupSize++;
        }
        if (groupSize != 0){
            for (int i = 6; i > -1; i--){
                if (MAP[i][col] == groupSize){
                    delPos.push_back({i, col});
                }
            }
        }
    }
    return;
}

void makeMapNew(vector<vector<int>>& MAP, vector<pair<int, int>>& delPos){
    // 0으로 바꿔주기
    for (auto p: delPos){
        int r = p.first, c = p.second;
        MAP[r][c] = 0;
    }
    // 빈칸 없애기
    for (int col = 0; col < 7; col++){
        vector<int> newCol;
        for (int row = 6; row >= 0; row--){
            if (MAP[row][col] != 0){
                newCol.push_back(MAP[row][col]);
            }
        }
        for (int i = 0; i < newCol.size(); i++){
            MAP[6-i][col] = newCol[i];
        }
        for (int i = newCol.size(); i < 7; i++){
            MAP[6-i][col] = 0;
        }
    }
    return;
}

int drop(vector<vector<int>> MAP, int col, int num){
    // 위에서 아래로 내려오며 0이 아닌 부분을 찾는다.(떨어뜨리기)
    bool flag = true;
    for (int row = 0; row < 7; row++){
        // 못떨어뜨리는 경우
        if (MAP[row][col] != 0 && row == 0) return 50;
        if (MAP[row][col] != 0){
            MAP[row-1][col] = num;
            flag = false;
            break;
        }
    }
    if (flag){
        MAP[6][col] = num;
    }
    // 더이상 바뀌지 않을 때까지 무한 반복.
    vector<pair<int, int>> delPos;
    while (true){
        delPos.clear();
        findDelPos(MAP, delPos);
        if (delPos.empty()){
            break;
        }
        makeMapNew(MAP, delPos);
    }
    int res = 0;
    for (int row = 0; row < 7; row++){
        for (int col = 0; col < 7; col++){
            if (MAP[row][col] != 0) res++;
        }
    }
    return res;
}

int main(void){
    vector<vector<int>> MAP(7, vector<int>(7, 0));
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            cin >> MAP[i][j];
        }
    }
    int num; cin >> num;
    int ans = 50;
    for (int col = 0; col < 7; col++){
        ans = min(ans, drop(MAP, col, num));
    }
    cout << ans;
}