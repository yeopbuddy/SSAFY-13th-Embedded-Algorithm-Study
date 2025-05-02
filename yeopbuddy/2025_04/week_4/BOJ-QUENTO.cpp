#include <iostream>
#include <vector>
using namespace std;
char arr[3][3];
bool visit[3][3];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int n, m;

vector<pair<int, int>> path;

void getpath(int stx, int sty, vector<pair<int, int>> way) { // dfs
    if (way.size() == (2 * m - 1)) {
        int val = 0;
        for (int i = 0; i < way.size(); i++) {
            int wx = way[i].first;
            int wy = way[i].second;
            char v = arr[wx][wy];
            if (i == 0) {
                val =  (v - '0');
            }
            else if (i % 2 == 0) {
                char op = arr[way[i - 1].first][way[i - 1].second];
                if (op == '-') {
                    val -= (v - '0');
                }
                else if (op == '+') {
                    val += (v - '0');
                }
            }
        }
        if (val == n) {
            path = way;
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = stx + dx[i];
        int ny = sty + dy[i];
        if (0 <= nx && nx < 3 && 0 <= ny && ny < 3 && !visit[nx][ny]) {
            visit[nx][ny] = true;
            way.push_back({ nx, ny });
            getpath(nx, ny, way);
            way.pop_back();
            visit[nx][ny] = false;
        }
    }
}


int main(){
    cin >> n >> m;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> arr[i][j];
        }
    }
    
    

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ('0' <= arr[i][j] && arr[i][j] <= '9') {
                vector<pair<int, int>> memory;
                visit[i][j] = true;
                memory.push_back({ i, j });
                getpath(i, j, memory);
                visit[i][j] = false;
            }
        }
    }
    if (path.size() != 0) {
        cout << "1\n";
        for (pair<int, int> p : path) {
            cout << p.first << " " << p.second << "\n";
        }
    }
    else {
        cout << "0";
    }
}