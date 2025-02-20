#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int N, M;
int start_x, start_y, end_x, end_y;
vector<vector<char>> arr; 
vector<vector<int>> visited;
queue<pair<int, int>> q;
vector<pair<int, int>> ghost;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void dfs(){
    q.push({start_x, start_y});
    visited[start_x][start_y] = 0;

    while(!q.empty()){
        auto[x, y] = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(0<=nx && nx<N && 0<=ny && ny<M && arr[nx][ny]!='#' && visited[nx][ny]==-1){
                q.push({nx, ny});
                visited[nx][ny] = visited[x][y] + 1;
            }
        }
    }
}

int main(int argc, char** argv){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    arr.resize(N, vector<char>(M));
    visited.resize(N, vector<int>(M, -1));

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 'D'){
                end_x = i;
                end_y = j;
            }
            else if(arr[i][j] == 'N'){
                start_x = i;
                start_y = j;
            }
            else if(arr[i][j] == 'G'){
                ghost.push_back({i, j});
            }
        }
    }

    dfs();
    string result;
    if(visited[end_x][end_y] == -1){
        result = "No";
    }
    else{
        bool flag = true;
        for(auto[x, y] : ghost){
            if(abs(x-end_x)+abs(y-end_y)<=visited[end_x][end_y]){
                flag = false;
                break;
            }
        }
        if(flag){
            result = "Yes";
        }
        else{
            result = "No";
        }
    }

    cout << result << '\n';
    
   return 0;
}