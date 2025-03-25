// 같은 색의 공 4개가 연속되면 팡 ~
// 연쇄 팡을 유도하려면 중간 쪽 색상 변경이 유리해보이지만
// 일단 첫 인덱스부터 마지막 인덱스까지 현재 인덱스를 포함한 
// 4개의 요소들을 따져보며 팡~ 할 수 있는 모든 경우를 고려해본다 !
// 고려하는 경우는 [현재, 현재 + 1, 현재 + 2, 현재 + 3] 부터 [현재 - 3, 현재 - 2, 현재 - 1, 현재]의 총 4가지 경우이다.

#include <iostream>
#include <vector>
using namespace std;
vector<int> RBYPANG;
int ANS;
void PANG(const vector<int>& originalRBY, int target, int change) {
    vector<int> RBY = originalRBY;
    int LEFT_POINTER = target; int RIGHT_POINTER = target; size_t VECSIZE = RBY.size();

    while (true){ // 초기 팡 : 왼쪽 범위 구하기
        if (LEFT_POINTER - 1 >= 0 && RBY[LEFT_POINTER - 1] == change) {
            LEFT_POINTER--;
        }
        else {
            break;
        }
    }

    while (true) { // 초기 팡 : 오른쪽 범위 구하기
        if (RIGHT_POINTER + 1 < VECSIZE && RBY[RIGHT_POINTER + 1] == change) {
            RIGHT_POINTER++;
        }
        else {
            break;
        }
    }
    
    for (int i = LEFT_POINTER; i <= RIGHT_POINTER; i++) { // 초기 팡이 가능한 경우에만 함수에 도달할 수 있으므로 일단 범위 검사 없이 LP부터 RP까지 팡
        RBY[i] = 0;
    }
    
    while (true) { // 연쇄 팡 시뮬레이션 : LP 기점, RP 기점을 추가로 선언 후, 두 기점을 기준으로 LP와 RP의 이동량의 합이 4 이상이면 PANG!
        int LP_BEFORE = LEFT_POINTER; int RP_BEFORE = RIGHT_POINTER;
        // 초기값 세팅
        if (LEFT_POINTER - 1 >= 0) {
            change = RBY[LEFT_POINTER - 1];
        }
        else if (RIGHT_POINTER + 1 < VECSIZE) {
            change = RBY[RIGHT_POINTER + 1];
        }
        else {
            break;
        }

        while (true) { // 연쇄 팡 : 왼쪽 범위 구하기
            if (LEFT_POINTER - 1 >= 0 && RBY[LEFT_POINTER - 1] == change) {
                LEFT_POINTER--;
            }
            else {
                break;
            }
        }

        while (true) { // 연쇄 팡 : 오른쪽 범위 구하기
            if (RIGHT_POINTER + 1 < VECSIZE && RBY[RIGHT_POINTER + 1] == change) {
                RIGHT_POINTER++;
            }
            else {
                break;
            }
        }
        if ((LP_BEFORE - LEFT_POINTER) + (RIGHT_POINTER - RP_BEFORE) >= 4) { // 색깔이 같은 공이 4개 이상 있을 경우 팡!
            for (int i = LEFT_POINTER; i < LP_BEFORE; i++) {
                RBY[i] = 0;
            }
            for (int i = RP_BEFORE; i <= RIGHT_POINTER; i++) {
                RBY[i] = 0;
            }
        }
        else {
            break;
        }
    }
    int cnt = 0;
    for (size_t i = 0; i < RBY.size(); i++) {
        if (RBY[i] != 0) {
            cnt++;
        }
    }
    if (cnt < ANS) {
        ANS = cnt;
    }
}

int main() {
    int n; cin >> n; RBYPANG.resize(n); ANS = n;
    for (int i = 0; i < n; i++) {
        cin >> RBYPANG[i];
    }
    
    for (int i = 0; i < n; i++) {
        if (i + 3 < n && RBYPANG[i + 1] == RBYPANG[i + 2] && RBYPANG[i + 2] == RBYPANG[i + 3]) { // [현재, 현재 + 1, 현재 + 2, 현재 + 3]
            PANG(RBYPANG, i, RBYPANG[i + 1]);
        }
        if (i + 2 < n && i - 1 >= 0 && RBYPANG[i - 1] == RBYPANG[i + 1] && RBYPANG[i + 1] == RBYPANG[i + 2]) { // [현재 - 1, 현재, 현재 + 1, 현재 + 2]
            PANG(RBYPANG, i, RBYPANG[i + 1]);
        }
        if (i + 1 < n && i - 2 >= 0 && RBYPANG[i - 2] == RBYPANG[i - 1] && RBYPANG[i - 1] == RBYPANG[i + 1]) { // [현재 - 2, 현재 - 1, 현재, 현재 + 1]
            PANG(RBYPANG, i, RBYPANG[i + 1]);
        }
        if (i - 3 >= 0 && RBYPANG[i - 3] == RBYPANG[i - 2] && RBYPANG[i - 2] == RBYPANG[i - 1]) { // [현재 - 3, 현재 - 2, 현재 - 1, 현재]
            PANG(RBYPANG, i, RBYPANG[i - 1]);
        }
    }
    cout << ANS;
}