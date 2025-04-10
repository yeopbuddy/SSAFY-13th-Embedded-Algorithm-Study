// 3987번 보이저 1호
// 구현
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

int reflect(char mirror, int now_direction) {
    // mirror가 '\'일 때
    if (mirror == '\\') {
        if (now_direction == 0) return 3;
        else if (now_direction == 3) return 0;
        else if (now_direction == 1) return 2;
        else return 1;
    }
    // mirror가 '/'일 때
    else {
        if (now_direction == 0) return 1;
        else if (now_direction == 1) return 0;
        else if (now_direction == 2) return 3;
        else return 2;
    }
}

int main(){
    fastio;
    int N, M; cin >> N >> M;
    // 그래프 입력
    vector<string> graph(N);
    for (int i = 0; i < N; i++){
        cin >> graph[i];
    }
    // 초기 탐사선 위치 (입력은 1-indexed이므로 0-indexed로 조정)
    int P_r, P_c; cin >> P_r >> P_c;
    P_r--; P_c--;
    // 방향 정보: 0: 'U', 1: 'R', 2: 'D', 3: 'L'
    char dirChar[4] = {'U', 'R', 'D', 'L'};
    int dr[4] = {-1, 0, 1,  0};
    int dc[4] = { 0, 1, 0, -1};
    int max_time = 0;       // 각 시작 방향에서 도달한 최대 시간
    int max_time_dir = 0;   // 최대 시간을 주는 시작 방향
    bool voyager_flag = false;  // 무한 루프(“Voyager”)가 발생한 경우
    // 시작 방향 0 ~ 3에 대하여 시뮬레이션
    for (int start_direction = 0; start_direction < 4; start_direction++){
        int now_direction = start_direction;
        int now_pos_r = P_r, now_pos_c = P_c; // 현재 위치
        int trigger = 0;    // 탐사선이 초기 위치(P_r, P_c)를 지난 횟수
        int time_counter = 0;
        bool infinite = false;
        while (true) {
            // 만약 탐사선이 초기 위치를 10번 초과하여 지난다면 무한 루프라고 판단
            if (trigger > 10) {
                infinite = true;
                break;
            }
            // 범위를 벗어나면 종료
            if (now_pos_r < 0 || now_pos_r >= N || now_pos_c < 0 || now_pos_c >= M)
                break;
            // 'C'인 경우 종료
            if (graph[now_pos_r][now_pos_c] == 'C')
                break;
            
            // 현재 위치에 거울이 있으면 반사 처리
            if (graph[now_pos_r][now_pos_c] == '/' || graph[now_pos_r][now_pos_c] == '\\') {
                now_direction = reflect(graph[now_pos_r][now_pos_c], now_direction);
            }
            // 현재 위치가 초기 위치라면 trigger 카운트 증가
            if (now_pos_r == P_r && now_pos_c == P_c)
                trigger++;
            // 다음 위치로 이동
            now_pos_r += dr[now_direction];
            now_pos_c += dc[now_direction];
            time_counter++;
        }
        // 무한 루프 상황이면 바로 결과 출력 후 종료
        if (infinite) {
            cout << dirChar[start_direction] << "\n";
            cout << "Voyager" << "\n";
            voyager_flag = true;
            break;
        }
        // 최대로 오래 머문 경우 업데이트
        if (time_counter > max_time) {
            max_time = time_counter;
            max_time_dir = start_direction;
        }
    }
    if (!voyager_flag) {
        cout << dirChar[max_time_dir] << "\n";
        cout << max_time << "\n";
    }
    return 0;
}
