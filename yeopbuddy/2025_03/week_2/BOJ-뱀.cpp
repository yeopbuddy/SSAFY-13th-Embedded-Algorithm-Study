#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int main(){
    int n, k, r, c, l, x; char a; cin >> n >> k;
    vector<vector<int>> GAMEMAP (n, vector<int>(n, 0));
    for(int i = 0; i < k; i++){
        cin >> r >> c;
        GAMEMAP[r-1][c-1] = 1;
    }
    cin >> l;
    int ct = 1, cx = 0, cy = 0, cd = 0;
    int dx[4] = {0,1,0,-1}; // D(우회전) : cd++;
    int dy[4] = {1,0,-1,0}; // L(좌회전) : cd--;
    deque<pair<int, int>> SNAKE;
    SNAKE.push_back(make_pair(cx, cy));
    //cout << "time : " << 0 << ", head : (" << cx << ", " << cy << "), dir : (" << dx[cd] << ", " << dy[cd] << ")\n";
    for(int i = 0; i < l; i++){
        cin >> x >> a;
        // 받고, x초가 되기 전까지 simulate. x초때 회전(c) 액션 하기.
        for(ct; ct <= x; ct++){  // ct(시간) 범위 맞는지 확인
            int nx = SNAKE[0].first + dx[cd];
            int ny = SNAKE[0].second + dy[cd];
            if(0 <= nx && nx < n && 0 <= ny && ny < n && GAMEMAP[nx][ny] != 2){
                SNAKE.push_front(make_pair(nx, ny));
                if(GAMEMAP[nx][ny] == 0){ // 사과가 아닌 경우
                    GAMEMAP[SNAKE[SNAKE.size() - 1].first][SNAKE[SNAKE.size() - 1].second] = 0; 
                    SNAKE.pop_back(); // 마지막거 비우기
                }
                GAMEMAP[nx][ny] = 2;
                //cout << "time : " << ct << ", head : (" << nx << ", " << ny << "), dir : (" << dx[cd] << ", " << dy[cd] << ")\n";
            }
            else{
                //cout <<"breakd"<<"\n";
                cout << ct;
                return 0;
            }
        }
        // TURN Direction
        if(a == 'D'){
            cd++; cd%=4;
        }
        else{
            cd+=3; cd%=4;
        }
    }
    // 여기서 이제 끝날때까지 뱀 직진시키기
    while(true){
        int nx = SNAKE[0].first + dx[cd];
        int ny = SNAKE[0].second + dy[cd];
        if(0 <= nx && nx < n && 0 <= ny && ny < n && GAMEMAP[nx][ny] != 2){
            SNAKE.push_front(make_pair(nx, ny));
            if(GAMEMAP[nx][ny] == 0){ // 1인 경우(사과)에는 pop 안함
                GAMEMAP[SNAKE[SNAKE.size() - 1].first][SNAKE[SNAKE.size() - 1].second] = 0;
                SNAKE.pop_back();  // 마지막거 비우기
            }
            GAMEMAP[nx][ny] = 2;
            // cout << "time : " << ct << ", head : (" << nx << ", " << ny << "), dir : (" << dx[cd] << ", " << dy[cd] << ")\n";
        }
        else{
            cout << ct;
            break;
        }
        ct++;
    }
    return 0;
}