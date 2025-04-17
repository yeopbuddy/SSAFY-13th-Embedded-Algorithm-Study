#include <iostream>
#define endl '\n'

#include <algorithm>
#include <array>
#include <cctype>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using namespace std;

constexpr int board_size = 5;

class Maze2D
{
   public:
    void RotateRight()
    {
        array<array<int, board_size>, board_size> copy(maze);
        for (int r = 0; r < board_size; r++)
        {
            for (int c = 0; c < board_size; c++) maze[c][board_size - 1 - r] = copy[r][c];;
        }
    }

    array<int, board_size>& operator[](int idx)
    {
        return maze[idx];
    }

   private:
    array<array<int, board_size>, board_size> maze;
};

class Maze3D
{
   public:
    Maze3D()
    {
        for (auto& maze_2d : maze) maze_2d = new Maze2D;
        sort(maze.begin(), maze.end());
    }

    bool SetNextPermutation()
    {
        return next_permutation(maze.begin(), maze.end());
    }

    ~Maze3D()
    {
        for (auto& maze_2d : maze) delete maze_2d;
    }

    Maze2D& operator[](int idx)
    {
        return *maze[idx];
    }

   private:
    array<Maze2D*, board_size> maze;
};

int dz[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dx[] = {0, 0, 0, 0, 1, -1};

class PathFinder
{
   public:
    PathFinder() : maze() {}

    void InputMaze()
    {
        for (int z = 0; z < board_size; z++)
            for (int y = 0; y < board_size; y++)
                for (int x = 0; x < board_size; x++) cin >> maze[z][y][x];
    }

    int FindPath()
    {
        min_path = numeric_limits<int>::max();
        bool ret = true;
        while (ret)
        {
            TestAllRotateCase();
            ret = maze.SetNextPermutation();
        }
        if (min_path == numeric_limits<int>::max()) min_path = -1;
        return min_path;
    }

   private:
    int min_path;
    Maze3D maze;

    void TestAllRotateCase(int depth = 0)
    {
        if (depth == board_size)
        {
            BFS();
            return;
        }
        else
        {
            for (int loop = 0; loop < 4; loop++)
            {
                TestAllRotateCase(depth + 1);
                maze[depth].RotateRight();
            }
            return;
        }
    }

    void BFS()
    {
        struct status
        {
            int z, y, x, val;
        };

        queue<status> bfs_que;
        vector<vector<vector<int>>> visited(
            board_size, vector<vector<int>>(board_size, vector<int>(board_size, false)));

        bfs_que.push({0, 0, 0, 0});
        visited[0][0][0] = true;

        while (!bfs_que.empty())
        {
            auto cur_stat = bfs_que.front();
            bfs_que.pop();

            if (cur_stat.val >= min_path)
                continue;                

            if (IsEscape(cur_stat.z, cur_stat.y, cur_stat.x))
            {
                min_path = cur_stat.val;
                continue;
            }

            for (int dir = 0; dir < 6; dir++)
            {
                status next_stat = {cur_stat.z + dz[dir], cur_stat.y + dy[dir],
                                    cur_stat.x + dx[dir], cur_stat.val + 1};

                if (CheckBound(next_stat.z, next_stat.y, next_stat.x) &&
                    maze[next_stat.z][next_stat.y][next_stat.x] == 1 &&
                    !visited[next_stat.z][next_stat.y][next_stat.x])
                {
                    visited[next_stat.z][next_stat.y][next_stat.x] = true;
                    bfs_que.push(next_stat);
                }
            }
        }
    }

    bool CheckBound(int z, int y, int x)
    {
        return -1 < z && z < board_size && -1 < y && y < board_size && -1 < x && x < board_size;
    }

    bool IsEscape(int z, int y, int x)
    {
        return z == board_size - 1 && y == board_size - 1 && x == board_size - 1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    PathFinder path_finder;
    path_finder.InputMaze();
    int answer = path_finder.FindPath();

    cout << answer << endl;

    return 0;
}