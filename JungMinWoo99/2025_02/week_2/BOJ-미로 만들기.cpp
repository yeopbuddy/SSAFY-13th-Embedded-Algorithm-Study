#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using IntP = pair<int, int>;

#define DIR_NUM (4)

// 시계방향 회전 배열
int dy[] = {1, 0, -1, 0};
int dx[] = {0, -1, 0, 1};

class Hongjun {
   private:
    int cur_dir = 0;
    vector<IntP> move_record;

    int min_y;
    int min_x;

    IntP getBoardSize() {
        min_y = INT_MAX;
        min_x = INT_MAX;
        int max_y = INT_MIN;
        int max_x = INT_MIN;
        for (auto i : move_record) {
            if (min_y > i.first)
                min_y = i.first;
            if (min_x > i.second)
                min_x = i.second;

            if (max_y < i.first)
                max_y = i.first;
            if (max_x < i.second)
                max_x = i.second;
        }

        return make_pair(max_y - min_y + 1, max_x - min_x + 1);
    }

   public:
    Hongjun() : move_record(0) {
        move_record.push_back(make_pair(0, 0));
    }

    void moving(char m) {
        switch (m) {
            case 'F': {
                IntP cur_pos = move_record.back();
                move_record.push_back(make_pair(cur_pos.first + dy[cur_dir], cur_pos.second + dx[cur_dir]));
                break;
            }
            case 'R': {
                cur_dir += 1;
                cur_dir %= DIR_NUM;
                break;
            }
            case 'L': {
                cur_dir += 3;
                cur_dir %= DIR_NUM;
                break;
            }
            default:
                break;
        }
    }

    void draw(vector<vector<char>>& buf) {
        IntP size = getBoardSize();
        
        int size_y = size.first;
        int size_x = size.second;
        // cout<<size_y<<' '<<size_x<<endl;
        buf.resize(size_y);
        for (auto &v : buf)
            v.resize(size_x, '#');
        for (auto r : move_record)
            buf[r.first - min_y][r.second - min_x] = '.';
    }
};
main(void) {
    Hongjun hong;
    int N;
    cin >> N;
    string in;
    cin >> in;
    for (int i = 0; i < N; i++)
        hong.moving(in[i]);

    vector<vector<char>> buf;
    hong.draw(buf);

    for(int i = 0;i<buf.size();i++)
    {
        for(int l = 0;l<buf[0].size();l++)
            cout<< buf[i][l];
        if(i!=buf.size()-1)
            cout<<endl;
    }

    return 0;
}