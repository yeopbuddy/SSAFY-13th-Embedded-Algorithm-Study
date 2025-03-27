#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

#define PANG 4

struct BallGroup
{
    int color;
    int cnt;

    BallGroup(int color):color(color),cnt(1){}
};

class RBYGo
{
public:
    RBYGo(const vector<int>& input)
    {
        for(auto ball:input)
        {
            if(RBY_buf.empty()||RBY_buf.back().color != ball)
                RBY_buf.emplace_back(ball);
            else
                RBY_buf.back().cnt++;
        }
    }

    int getMaxRemovedBallCnt()
    {
        for(int idx = 0;idx<RBY_buf.size();idx++)
            tryPang(idx);
        return max_removed_balls;
    }

private:
    int max_removed_balls = 0;
    vector<BallGroup> RBY_buf;

    bool isValidIdx(int idx)
    {
        return -1 < idx && idx<RBY_buf.size();
    }

    void tryPang(int target_idx)
    {
        vector<int> dir = {-1, 1};
        for(int d: dir)
        {
            int abj_ball_group = target_idx + d;
            if(!isValidIdx(abj_ball_group))
                continue;

            RBY_buf[target_idx].cnt++;
            RBY_buf[abj_ball_group].cnt--;
            
            int side_idx_1 = abj_ball_group;
            int side_idx_2 = target_idx - d;

            int cur_group_size = RBY_buf[target_idx].cnt;
            while(isValidIdx(side_idx_1)&&(RBY_buf[side_idx_1].color == RBY_buf[target_idx].color || RBY_buf[side_idx_1].cnt == 0))
            {
                cur_group_size += RBY_buf[side_idx_1].cnt;
                side_idx_1 += d;
            }

            if(cur_group_size >= PANG)
            {
                int removed_ball_cnt = cur_group_size;

                int btm_idx = min(side_idx_1, side_idx_2);
                int up_idx = max(side_idx_1, side_idx_2);
                removed_ball_cnt += doPang(btm_idx, up_idx);

                max_removed_balls = max(max_removed_balls, removed_ball_cnt);
            }

            RBY_buf[target_idx].cnt--;
            RBY_buf[abj_ball_group].cnt++;
        }
    }

    int doPang(int btm_idx, int up_idx)
    {
        if(btm_idx < 0 || up_idx >= RBY_buf.size())
            return 0;
        int ret = 0;
        if(RBY_buf[btm_idx].color == RBY_buf[up_idx].color)
        {
            int ball_group_size = RBY_buf[btm_idx].cnt + RBY_buf[up_idx].cnt;
            if(ball_group_size >= PANG)
                ret = ball_group_size + doPang(btm_idx-1,up_idx+1);
        }
        
        return ret;
    }
};

int main(void)
{
    int N;
    cin>>N;
    vector<int> input;
    for(int loop = 0;loop<N;loop++)
    {
        int in;
        cin >> in;
        input.push_back(in);
    }

    RBYGo rby_go(input);

    int answer = N - rby_go.getMaxRemovedBallCnt();
    cout<<answer<<endl;
    return 0;
}