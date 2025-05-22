// 모든 칸에 대해서 BFS를 돌리면서 밖으로 새나가는 지 판단한다.
// 밖으로 새나갈 경우(deque에서 pop된 좌표가 0의 값을 가진 경우) water_amount에 0으로 저장
// 밖으로 새지 않은 경우 테두리 중 최소 값에서 빼준 값을 저장한다.(이 경우 방문했던 점들을 한 영역으로 인식하고 모두 방문처리)

#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <tuple>
using namespace std;

int n, m;
bool visit[51][51]; // 매번 수행하는 BFS에 대해 재방문 방지용
bool vvisit[51][51]; // 물이 채워질 수 있는 양이 정해진 좌표에 대해 재방문 방지용
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
vector<vector<int>> SwimmingPool; // INPUT 받기용
vector<vector<int>> WaterAmount; // 매 칸바다 채울 수 있는 물의 양 저장용

void CheckValid(int x, int y){
    memset(visit, false, sizeof(visit));
    deque<pair<int, int>> dq; vector<pair<int, int>> subvec; // deque : BFS, vector : 좌표 저장용
    dq.push_back({x, y}); subvec.push_back({x, y}); // vector를 추가로 쓴 이유 : 물 채울 수 있는 영역 기록하고 한번에 채워 main문에서 재탐색 방지
    visit[x][y] = true;
    int val = SwimmingPool[x][y]; // 외부로 흘러나감을 비교하기 위함
    bool flowoutside = false; // 외부로 흘러나감을 탐지하기 위함
    
    while(!dq.empty()){
        int px = dq.front().first;
        int py = dq.front().second;
        if(px == 0 || py == 0 || px == n - 1 || py == m - 1){ // 테두리는 무조건 새어나감
            flowoutside = true;
            break;
        }
        dq.pop_front();
        for(int i = 0; i < 4; i++){
            int nx = px + dx[i];
            int ny = py + dy[i];
            if((0 <= nx && nx < n) && (0 <= ny && ny < m) && !visit[nx][ny] && SwimmingPool[nx][ny] <= val){
                visit[nx][ny] = true;
                dq.push_back({nx, ny});
                subvec.push_back({nx, ny});
            }
        }
    }
    if(!flowoutside){ // x, y에 대해 BFS로 탐색한 후에, 외부로 흘러나가지 않는 경우
        int minwall = 1e9;
        for(pair<int, int>p : subvec){ // 좌표들을 순회하며 영역을 둘러싼 벽들 중 가장 낮은 높이 찾음
            for(int i = 0; i < 4; i++){
                int nx = p.first + dx[i];
                int ny = p.second + dy[i];
                if((0 <= nx && nx < n) && (0 <= ny && ny < m) && !visit[nx][ny]){ // 이미 방문한 점 방문 못하게 처리 : 영역 내부를 벽으로 인식하지 못하게
                    minwall = min(minwall, SwimmingPool[nx][ny]);
                }
            }   
        }
        for(pair<int, int>p : subvec){
            WaterAmount[p.first][p.second] = minwall - SwimmingPool[p.first][p.second];
            vvisit[p.first][p.second] = true; // 물을 채운 모든 좌표들에 대해 방문 처리 : main문에서 재탐색 방지
        }
    }else{
        WaterAmount[x][y] = 0;
        vvisit[x][y] = true; // 물이 흘러나간 경우, 해당 좌표만 방문 처리(BFS를 통해 방문한 다른 좌표들 중 물이 채워질 수도 있기 때문 : 해당 좌표를 시작점으로 BFS 탐색해보아야 암)
    }
    dq.clear(); subvec.clear();
}

int main(){
    cin >> n >> m;
    SwimmingPool.resize(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char c; cin >> c;
            SwimmingPool[i][j] = c - '0';
        }
    }
    
    WaterAmount.resize(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!vvisit[i][j]){
                CheckValid(i, j);    
            }
        }
    }
    int total = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            total += WaterAmount[i][j];
        }
    }
    cout << total;
    return 0;
}