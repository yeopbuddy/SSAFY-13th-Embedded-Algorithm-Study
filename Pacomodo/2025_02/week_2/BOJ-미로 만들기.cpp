// 1347번 미로 만들기
// 구현
/*
접근 방법:
넉넉하게 300*300크기의 배열을 선언.
이후 한 가운데서 시작해서 탐색
이후에 필요없는 벽 제거 후 출력
*/
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    fastio;
    int N; cin >> N;
    string S; cin >> S;
    vector<int> dr = {1, 0, -1, 0}, dc = {0, -1, 0, 1};
    int ndir = 0, nr = 150, nc = 150;
    vector<vector<char>> M(300, vector<char>(300, '#'));
    M[nr][nc] = '.';
    int minr = 150, maxr = 150, minc = 150, maxc = 150;
    for (char op: S){
        if (op == 'R'){
            ndir++;
            ndir %= 4;
        }
        else if (op == 'L'){
            ndir--;
            if (ndir < 0) ndir += 4;
        }
        else{
            nr += dr[ndir]; nc += dc[ndir];
            M[nr][nc] = '.';
            if (nr < minr) minr = nr;
            if (nc < minc) minc = nc;
            if (nr > maxr) maxr = nr;
            if (nc > maxc) maxc = nc;
        }
    }
    for (int i = minr; i <= maxr; i++){
        for (int j = minc; j <= maxc; j++){
            cout << M[i][j];
        }
        cout << endl;
    }
    return 0;
}