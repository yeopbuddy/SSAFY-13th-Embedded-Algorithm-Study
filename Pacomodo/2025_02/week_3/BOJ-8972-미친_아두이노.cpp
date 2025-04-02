// 8972번 미친 아두이노
// 구현
/*
접근 방법:

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int main(void){
    int R, C; cin >> R >> C;
    int dr[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
    int dc[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    int cdr[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int cdc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    vector<pair<int, int>> crazyRobots;
    int Jongsu_r, Jongsu_c;
    char character;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            cin >> character;
            if (character == 'I'){
                Jongsu_r = i, Jongsu_c = j;
            }
            if (character == 'R'){
                crazyRobots.push_back({i, j});
            }
        }
    }
    string S; cin >> S;
    for (int time = 1; time <= S.size(); time++){
        int JongsuMoveIdx = (int)(S[time-1]-'1');
        // 1. 종수를 움직인다.
        Jongsu_r += dr[JongsuMoveIdx];
        Jongsu_c += dc[JongsuMoveIdx];
        // 1.1 미친 아두이노가 없는 경우;
        if (crazyRobots.empty()){
            continue;
        }
        // 2. 종수가 미친 아두이노를 만날 경우
        pair<int, int> Jongsu = {Jongsu_r, Jongsu_c};
        if (find(crazyRobots.begin(), crazyRobots.end(), Jongsu) != crazyRobots.end()){
            cout << "kraj " << time;
            return 0;
        }
        // 3. 아두이노 움직이기
        for (int i = 0; i < crazyRobots.size(); i++){
            int r = crazyRobots[i].first, c = crazyRobots[i].second;
            int newr = r, newc = c, minD = R*C;
            for (int j = 0; j < 8; j++){
                int nr = r+cdr[j], nc = c+cdc[j];
                if (0 <= nr && nr < R && 0 <= nc && nc < C){
                    int d = abs(Jongsu_r - nr) + abs(Jongsu_c - nc);
                    if (d < minD){
                        minD = d;
                        newr = nr, newc = nc;
                    }
                }
            }
            crazyRobots[i] = {newr, newc};
        }
        // 4. 미친 아두이노가 종수가 있는 칸으로 간 경우 게임이 끝난다.
        for (int i = 0; i < crazyRobots.size(); i++){
            int r = crazyRobots[i].first, c = crazyRobots[i].second;
            if (r == Jongsu_r && c == Jongsu_c){
                cout << "kraj " << time;
                return 0;
            }
        }
        // 5. 2개 또는 그 이상의 미친 아두이노가 있는 경우 그 칸의 아두이노는 모두 파괴된다.
        vector<pair<int, int>> newCrazyRobots;
        sort(crazyRobots.begin(), crazyRobots.end());
        pair<int, int> before = crazyRobots[0];
        bool noAdd = false;
        for (int i = 1; i < crazyRobots.size(); i++){
            if (crazyRobots[i] == before){
                noAdd = true;
            }
            else if(crazyRobots[i] != before && noAdd){
                before = crazyRobots[i];
                noAdd = false;
            }
            else if (crazyRobots[i] != before && !noAdd){
                newCrazyRobots.push_back(before);
                before = crazyRobots[i];
            }
        }
        if (!noAdd){
            newCrazyRobots.push_back(before);
        }
        crazyRobots = newCrazyRobots;
    }
    vector<vector<char>> MAP(R, vector<char>(C, '.'));
    MAP[Jongsu_r][Jongsu_c] = 'I';
    for (auto p: crazyRobots){
        MAP[p.first][p.second] = 'R';
    }
    for (auto row: MAP){
        for (auto ele: row){
            cout << ele;
        }
        cout << endl;
    }
    return 0;
}