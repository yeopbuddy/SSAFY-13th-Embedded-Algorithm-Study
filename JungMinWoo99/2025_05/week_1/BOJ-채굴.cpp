#include <iostream>
#define endl '\n'

#include <algorithm>
#include <cctype>
#include <limits>
#include <queue>
#include <string>
#include <vector>

using namespace std;

#define MAX_S 1e6

int dy[] = {-1, 0, 1, 0};
int dx[] = {0, -1, 0, 1};

struct MinePos
{
    int y;
    int x;
    int power;

    bool operator>(const MinePos& b) const
    {
        return this->power > b.power;
    }
};

class DigRock
{
   public:
    DigRock(int n, int m, int k)
        : N(n), M(m), K(k), board(n, vector<int>(m, 0)), dig_cnt(MAX_S, 0)
    {
        for (auto& row : board)
            for (auto& ele : row) cin >> ele;
    }

    int FindAnswer()
    {
        vector<vector<int>> visited(N, vector<int>(M, false));
        priority_queue<MinePos,vector<MinePos>,greater<MinePos>> bfs_que;

        // 시작 채굴 위치 저장
        for (int x = 0; x < M; x++) bfs_que.push({0, x, board[0][x]});
        for (int y = 1; y < N; y++)
        {
            bfs_que.push({y, 0, board[y][0]});
            bfs_que.push({y, M - 1, board[y][M - 1]});
        }

        while (!bfs_que.empty())
        {
            auto cur_dig_pos = bfs_que.top();
            bfs_que.pop();

            if (visited[cur_dig_pos.y][cur_dig_pos.x])
                continue;
            else{
                visited[cur_dig_pos.y][cur_dig_pos.x] = true;
                dig_cnt[cur_dig_pos.power]++;
            }

            for (int dir = 0; dir < 4; dir++)
            {
                int next_y = cur_dig_pos.y + dy[dir];
                int next_x = cur_dig_pos.x + dx[dir];
                if (CheckBound(next_y, next_x) && !visited[next_y][next_x])
                {
                    bfs_que.push({next_y, next_x, max(cur_dig_pos.power, board[next_y][next_x])});
                }
            }
        }

        int sum = 0;
        int answer = -1;
        while(sum < K){
            answer++;
            sum += dig_cnt[answer];
        }
        for(auto val: dig_cnt)
            cout << val <<' ';
        cout<<endl;

        return answer;
    }

   private:
    int N, M, K;
    vector<vector<int>> board;
    vector<int> dig_cnt;

    bool CheckBound(int y, int x)
    {
        return -1 < y && y < N && -1 < x && x < M;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    DigRock dig_rock(N,M,K);
    cout<<dig_rock.FindAnswer();

    return 0;
}