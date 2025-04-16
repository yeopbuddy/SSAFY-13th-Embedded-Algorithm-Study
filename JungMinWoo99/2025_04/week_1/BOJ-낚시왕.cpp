#include <iostream>
#define endl '\n'

#include <algorithm>
#include <cctype>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;
enum Dir
{
    None,
    Up,
    Down,
    Right,
    Left
};

Dir FlipDir(Dir d)
{
    if (d == Up || d == Right)
        return Dir(d + 1);
    else
        return Dir(d - 1);
}

pair<int, int> dir[] = {
    {0, 0},
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
};

struct Shark
{
    static int center;
    int r, c, s, d, z;
    bool operator<(const Shark &b)
    {
        if (abs(b.c - center) == abs(this->c - center))
        {
            if (b.c - center == this->c - center)
            {
                if (b.r == this->r)
                    return this->z > b.z;
                else
                    return this->r < b.r;
            }
            else
                return this->c < b.c;
        }

        return abs(this->c - center) < abs(b.c - center);
    }

    bool operator==(const Shark &b) // comp pos
    {
        return this->c == b.c && this->r == b.r && this->z < b.z;
    }
};

int Shark::center;

class FishingKing
{
public:
    FishingKing(int r, int c, int m) : R(r), C(c), M(m), cur_angler(0)
    {
        for (int loop = 0; loop < M; loop++)
        {
            int r, c, s, d, z;
            cin >> r >> c >> s >> d >> z;
            shark_que.push_back({r - 1, c - 1, s, d, z});
        }
    }

    int FishingAll()
    {
        int answer = 0;
        while (cur_angler < C)
        {
            Shark::center = cur_angler;
            sort(shark_que.begin(), shark_que.end());
            answer += Fishing();
            MoveAllShark();

            sort(shark_que.begin(), shark_que.end());

            MergeShark();
            cur_angler++;
        }
        return answer;
    }

    void PrintShark()
    {
        for (auto &shark : shark_que)
            cout << shark.r << shark.c << shark.d << shark.z << endl;
        cout << endl;
    }

private:
    int cur_angler;
    int R, C, M;
    deque<Shark> shark_que;

    int Fishing()
    {
        if (shark_que.empty() || cur_angler != shark_que.front().c)
            return 0;
        int ret = shark_que.front().z;
        shark_que.pop_front();
        return ret;
    }

    void MoveShark(Shark &shark)
    {
        auto cal_pos = [](int len, int pos, int dir)
        {
            if (dir == 0)
                return pos;
            else
            {
                int a = abs(pos) % (2 * len - 2);
                int b = a < len ? a : (2 * len - 2) - a;
                return b;
            }
        };

        auto cal_dir = [](int len, int pos, int dir)
        {
            if (dir == 0)
                return dir;
            else
            {
                if (0 <= pos && pos < len)
                    return dir;
                else
                    return (abs(pos) / (len - 1)) % 2 == 0 ? 1 : -1;
            }
        };
        pair<int, int> cur_pos = {shark.r, shark.c};
        pair<int, int> next_pos = {
            cal_pos(R, shark.r + dir[shark.d].first * shark.s, dir[shark.d].first),
            cal_pos(C, shark.c + dir[shark.d].second * shark.s, dir[shark.d].second)};
        int next_dy = cal_dir(R, shark.r + dir[shark.d].first * shark.s, dir[shark.d].first);
        int next_dx = cal_dir(C, shark.c + dir[shark.d].second * shark.s, dir[shark.d].second);

        shark.r = next_pos.first;
        shark.c = next_pos.second;

        for (int d = 0; d < 5; d++)
            if (dir[d].first == next_dy && dir[d].second == next_dx)
                shark.d = (Dir)d;
    }

    void MoveAllShark()
    {
        for (auto &shark : shark_que)
            MoveShark(shark);
    }

    void MergeShark()
    {
        int loop_cnt = shark_que.size();
        for (int loop = 0; loop < loop_cnt; loop++)
        {
            auto front_shark = shark_que.front();
            shark_que.pop_front();

            if (shark_que.empty() || !(front_shark == shark_que.back()))
                shark_que.push_back(front_shark);
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int R, C, M;
    cin >> R >> C >> M;
    FishingKing fishing_king(R, C, M);
    int answer = fishing_king.FishingAll();
    cout << answer << endl;

    return 0;
}