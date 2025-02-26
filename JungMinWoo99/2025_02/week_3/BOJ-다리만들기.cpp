#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
#define endl '\n'

#include <queue>

using namespace std;

struct Coor {
    int y;
    int x;
    int w;
};

constexpr int DIR_NUM = 4;
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

class Bridge {
   public:
   Bridge(int n, int m) : N(n), M(m), input_grid(n, vector<int>(m)), map(n, vector<int>(m, 0)), FF(n, vector<int>(m)),shortest_len(INT_MAX) {
        for (int i = 0; i < n; i++) {
            for (int l = 0; l < m; l++)
                cin >> input_grid[i][l];
        }
    }

    void drawMap() {
        int cnt = 1;
        for (int i = 0; i < N; i++)
            for (int l = 0; l < M; l++)
                if (map[i][l] == 0 && input_grid[i][l] == 1)
                    drawMap(i, l, cnt++);
    }

    int findShortestPath() {
        vector<int> is_visted(N*M,0);
		for (int i = 0; i < N; i++)
            for (int l = 0; l < M; l++)
                if (map[i][l] != 0 && is_visted[map[i][l]] == 0)
                {
                    is_visted[map[i][l]] = 1;
                    findShortestPath(i,l);
                }
        if(shortest_len == INT_MAX)
            return 2;
		return shortest_len;
    }

    void printMap() {
        for (auto &row : map) {
            for (auto i : row)
                cout << i<<' ';
            cout << endl;
        }
        cout<<endl;
    }

   private:
    int N, M;
    vector<vector<int>> input_grid;
    vector<vector<int>> map;
    vector<vector<int>> FF;

    int shortest_len;

    bool checkBound(int y, int x) {
        return -1 < y && y < N && -1 < x && x < M;
    }

    void drawMap(int y, int x, int sym) {
        queue<Coor> bfs_que;
        bfs_que.push({y, x, 1});
        while (!bfs_que.empty()) {
            auto cur = bfs_que.front();
            bfs_que.pop();
            if (map[cur.y][cur.x] == sym)
                continue;
            map[cur.y][cur.x] = sym;

            for (int i = 0; i < DIR_NUM; i++) {
                int next_y = cur.y + dy[i];
                int next_x = cur.x + dx[i];
                if (checkBound(next_y, next_x) && input_grid[next_y][next_x] == 1)
                    bfs_que.push({next_y, next_x, cur.w + 1});
            }
        }
    }

	void findShortestPath(int y, int x)
	{
		FF.assign(N,vector<int>(M,0));
        queue<Coor> start_bfs_que;
		queue<Coor> bfs_que;
        start_bfs_que.push({y, x, 1});
        while (!start_bfs_que.empty()) {
            auto cur = start_bfs_que.front();
            start_bfs_que.pop();
            if (FF[cur.y][cur.x] != 0)
                continue;

            bfs_que.push({cur.y,cur.x,1});
            FF[cur.y][cur.x] = 1;
			

            for (int i = 0; i < DIR_NUM; i++) {
                int next_y = cur.y + dy[i];
                int next_x = cur.x + dx[i];
                if (checkBound(next_y, next_x))
                    if (map[next_y][next_x] == map[y][x])
                        start_bfs_que.push({next_y, next_x, cur.w + 1});
            }
        }
        //printFF();
        FF.assign(N,vector<int>(M,0));
		while (!bfs_que.empty()) {
            auto cur = bfs_que.front();
            bfs_que.pop();
            if (FF[cur.y][cur.x] != 0)
                continue;
            if(map[cur.y][cur.x] != 0 && map[cur.y][cur.x] != map[y][x])
            {
                if (cur.w < shortest_len)
                    shortest_len = cur.w;
                break;
            }

            if(cur.w >= shortest_len)
                break;

            FF[cur.y][cur.x] = cur.w;
			

            for (int i = 0; i < DIR_NUM; i++) {
                int next_y = cur.y + dy[i];
                int next_x = cur.x + dx[i];
                if (checkBound(next_y, next_x))
                {
                    if (map[cur.y][cur.x] == map[y][x])
                    {
                        if (map[next_y][next_x] == map[y][x])
                            bfs_que.push({next_y, next_x, cur.w});
                        else
                            bfs_que.push({next_y, next_x, cur.w + 1});
                    }
                    else
                        if (map[next_y][next_x] != map[y][x])
                            bfs_que.push({next_y, next_x, cur.w + 1});
                }
            }
        }
        //printFF();
	}

    void printFF()
    {
        for (auto &row : FF) {
            for (auto i : row)
                cout << i<<' ';
            cout << endl;
        }
        cout<<endl;
    }
};

int main(void) {
    fastio;
    int N;
    cin >> N;
    Bridge bridge(N, N);
    bridge.drawMap();
	//bridge.printMap();
	cout << bridge.findShortestPath()-2;

    return 0;
}