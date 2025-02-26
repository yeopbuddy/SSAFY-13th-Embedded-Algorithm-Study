#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int main(){
    int arr[100][100] = {0};
    bool visi[100][100] = {false};
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
    // 2중 vector를 이용하여 area를 구분하고, 각 area에 해당하는 좌표들을 저장한다.
    vector<pair<int, int>> subarea;
    vector<vector<pair<int, int>>> area;
    deque<pair<int, int>> dq;
    int dx[4] = {0,0,1,-1};
    int dy[4] = {1,-1,0,0};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] == 1 && !visi[i][j]){
                visi[i][j] = true;
                dq.push_back(make_pair(i, j));
                while(dq.size() > 0){
                    int px = dq.front().first;
                    int py = dq.front().second;
                    subarea.push_back(make_pair(px, py));
                    dq.pop_front();
                    for(int k = 0; k < 4; k++){
                        int nx = px + dx[k];
                        int ny = py + dy[k];
                        if(0 <= nx && nx < n && 0 <= ny && ny < n && arr[nx][ny] == 1 && !visi[nx][ny]){
                            visi[nx][ny] = true;
                            dq.push_back(make_pair(nx, ny));
                        }
                    }
                }
                area.push_back(subarea);
                subarea.clear();
            }
        }
    }
    
    int mind = 200;
    int as = area.size();
    for(int i = 0; i < as; i++){
        for(int j = i + 1; j < as; j++){ // 완전탐색을 통해 각 area들을 비교한다.
            for(int k = 0; k < area[i].size(); k++){
                for(int p = 0; p < area[j].size(); p++){ // 완전탐색을 통해 선택된 두 area를 잇는 최단거리를 탐색한다.
                    int dd = abs(area[i][k].first - area[j][p].first) + abs(area[i][k].second - area[j][p].second); // 거리 계산 : 맨해튼 거리
                    if(dd < mind){ // 최단 거리를 갱신한다.
                        mind = dd;
                    }
                }   
            }
        }
    }
    cout << mind - 1; // 양식에 맞게 출력한다.
    return 0;
}