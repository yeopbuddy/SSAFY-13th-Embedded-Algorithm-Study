#include <vector>
#include <iostream>
#include <algorithm>

#include <array>
#include <queue>
#include <cmath>

#define DMG_MUL 3
#define ARR_SIZE 3
#define MAX_HIT 15

using namespace std;

class Puzzle
{
private:
    int scv_num;
    vector<int> hp;
    vector<vector<int>> hit_board;

    vector<int> col_cnt;
    vector<int> row_cnt;

    bool is_dead(int scv_num)
    {
        int dmg_sum = 0;
        for (int i = 0; i < ARR_SIZE; i++)
            dmg_sum += pow(DMG_MUL,i)*hit_board[scv_num][i];
        return dmg_sum >= hp[scv_num];
    }

public:
    Puzzle(int scv_num):scv_num(scv_num), hp(scv_num), hit_board(scv_num,vector<int>(ARR_SIZE,0)),row_cnt(scv_num),col_cnt(ARR_SIZE)
    {
        for(auto& i:hp)
            cin >> i;
    }

    void setHitcnt(int hit)
    {
        for(int& i:col_cnt)
            i = hit;
        for(int& i:row_cnt)
            i = hit;
    }

    bool backtrack(int y, int x)
    {
        if(x == 0 && y == scv_num)
            return true;

        bool ret = false;
        int max_val = min(row_cnt[y],col_cnt[x]);//해당 칸에 넣을 수 있는 최대값값
        for(int i = max_val;i>=0;i--)
        {
            hit_board[y][x] = i;
            row_cnt[y] -=i;
            col_cnt[x] -=i;

            if(is_dead(y))
                ret = backtrack(y+1,0);
            else if(x != ARR_SIZE - 1)
                ret = backtrack(y,x+1); 
            
            if(ret)
                break;

            row_cnt[y] +=i;
            col_cnt[x] +=i;
            hit_board[y][x] = 0;
        }

        return ret;
    } 
};

int main(void)
{
    int N;
    cin >> N;
    Puzzle m(N);
    int answer;
    for(answer = 1;answer<=MAX_HIT;answer++)
    {
        m.setHitcnt(answer);
        bool ret = m.backtrack(0,0);
        if(ret)
            break;
    }
    cout<<answer;
    return 0;
}