#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;
int n, m, k;
vector<vector<int>> CAVE;
bool visit[1001][1001];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int get(int pickaxe){
    int count = 0;
    memset(visit, false, sizeof(visit));
    deque<pair<int, int>> dq;
    for(int i = 0; i < n; i++) {
        if(CAVE[i][0] <= pickaxe && !visit[i][0]){
            visit[i][0] = true;
            dq.push_back({i, 0});
            count++;
        }
        if(CAVE[i][m-1] <= pickaxe && !visit[i][m-1]){
            visit[i][m-1] = true;
            dq.push_back({i, m-1});
            count++;
        }
    }
    for(int i = 1; i < m-1; i++) {
        if(CAVE[0][i] <= pickaxe && !visit[0][i]){
            visit[0][i] = true;
            dq.push_back({0, i});
            count++;
        }
    }
    while(!dq.empty()){
        int px = dq.front().first;
        int py = dq.front().second;
        dq.pop_front();
        for(int i = 0; i < 4; i++){
            int nx = px + dx[i];
            int ny = py + dy[i];
            if(0 <= nx && nx < n && 0 <= ny && ny < m && !visit[nx][ny] && CAVE[nx][ny] <= pickaxe){
                visit[nx][ny] = true;
                dq.push_back({nx, ny});
                count++;
            }
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> k;
    CAVE.resize(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> CAVE[i][j];
        }
    }
    
    int ans;
    int left = 1;
    int right = 1000000;
    
    while(left <= right){
        int mid = (left + right) / 2;
        int val = get(mid);
        // ans = left;
        // cout << "pickaxe : " << mid << " and get : " << val << " and left : " << left << " and right : " << right <<   "\n";
        if(val >= k){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    cout << ans;  
}
