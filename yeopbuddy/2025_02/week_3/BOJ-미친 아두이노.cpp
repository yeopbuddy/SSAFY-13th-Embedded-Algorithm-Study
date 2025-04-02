#include <iostream>
#include <string>
#include <vector>
using namespace std;

// int arr[100][100] = {0};
vector<pair<int, int>> JS;
vector<pair<int, int>> MA;

int dx[9] = {1,1,1,0,0,0,-1,-1,-1};
int dy[9] = {-1,0,1,-1,0,1,-1,0,1};

int MOVE(int mv, int n, int m){
    // move jong-su's ARDUINO
    JS[0].first += dx[mv-1];
    JS[0].second += dy[mv-1];
    
    int newJSX = JS[0].first;
    int newJSY = JS[0].second;
    int MAS = MA.size();
    
    // check
    for(int i = 0; i < MAS; i++){
        if(MA[i].first == newJSX && MA[i].second == newJSY){
            return -1;
        }
    }
    
    // move MAD ARDUINO
    int DUP[100][100] = {0};
    for(int i = 0; i < MA.size(); i++){
        int mind = 200; int mini = 0;
        for(int j = 0; j < 9; j++){
            if(j == 4){
                continue;
            }
            else{
                int newMAX = MA[i].first + dx[j];
                int newMAY = MA[i].second + dy[j];
                if(abs(newMAX - newJSX) + abs(newMAY - newJSY) < mind){
                    mind = abs(newMAX - newJSX) + abs(newMAY - newJSY);
                    mini = j;
                }
            }
        }
        MA[i].first += dx[mini];
        MA[i].second += dy[mini];
        DUP[MA[i].first][MA[i].second]++;
    }
    // check
    for(int i = 0; i < MAS; i++){
        if(MA[i].first == newJSX && MA[i].second == newJSY){
            return -1;
        }
    }
    // delete DUPLICATE
    MA.clear();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(DUP[i][j] == 1){
                MA.push_back(make_pair(i, j));
            }
        }
    }
    return 0;
}

int main(){
    int r, c;
    cin >> r >> c;
    char ch;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> ch;
            if(ch == 'I'){
                JS.push_back(make_pair(i, j));
            }
            else if(ch == 'R'){
                MA.push_back(make_pair(i, j));
            }
        }
    }
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++){
        int sti = s[i] - '0';
        int res = MOVE(sti, r, c);
        if (res == -1){
            cout << "kraj " << i + 1;
            return 0;
        }
    }
    char arr[100][100];
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            arr[i][j] = '.';
        }
    }
    arr[JS[0].first][JS[0].second] = 'I';
    for(int i = 0; i < MA.size(); i++){
        arr[MA[i].first][MA[i].second] = 'R';
    }
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cout << arr[i][j];
        }
        cout << "\n";
    }
}