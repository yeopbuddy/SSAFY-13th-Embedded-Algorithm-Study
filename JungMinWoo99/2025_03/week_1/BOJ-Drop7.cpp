#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <stack>

#define endl '\n'

using namespace std;

#define GRID_SIZE 7

class Drop7
{
public:
    Drop7(const vector<vector<int>>& input):grid(GRID_SIZE) {
        for(int col_num  = 0;col_num<GRID_SIZE;col_num++)
        {
            for(int i  = GRID_SIZE-1;i>-1;i--)
                grid[col_num].push_back(input[i][col_num]);
        }
        
        total_ball_cnt = 0;
        for(auto &row:grid)
            for(auto &cell:row)
                if(cell != 0)
                    total_ball_cnt++;
    }

    bool runGameLoopOnce()
    {
		/*
		프로그램 실행 절차
		1. 공중에 떠있는 공을 모두 바닥으로 이동
		2. 현재 존재하는 모든 그룹을 탐색하여 저장
		3. 각각의 그룹에서 사라지는 원소를 0으로 변경 
		*/

		// 절차 1: 공중에 떠있는 모든 공을 바닥으로 이동
        for(int i = 0;i<GRID_SIZE;i++)
            fallDownBall(grid[i]);

		// 절차 2 - 1: 모든 열 그룹을 탐색하여 저장
        int prev_cnt = total_ball_cnt;
        vector<stack<int*>> ball_groups;
        ball_groups.emplace_back();
        for(int row_num = 0;row_num<GRID_SIZE;row_num++)
        {
            for(int col_num = 0;col_num<GRID_SIZE;col_num++)
            {
                if(grid[row_num][col_num] == 0 && !ball_groups.back().empty())
                    ball_groups.emplace_back();
                else if(grid[row_num][col_num] != 0)
                    ball_groups.back().push(&grid[row_num][col_num]);
            }

            if(!ball_groups.back().empty())
                ball_groups.emplace_back();
        }

		// 절차 2 - 2: 모든 행 그룹을 탐색하여 저장
        for(int col_num = 0;col_num<GRID_SIZE;col_num++)
        {
            for(int row_num = 0;row_num<GRID_SIZE;row_num++)
            {
                if(grid[row_num][col_num] == 0 && !ball_groups.back().empty())
                    ball_groups.emplace_back();
                else if(grid[row_num][col_num] != 0)
                    ball_groups.back().push(&grid[row_num][col_num]);
            }

            if(!ball_groups.back().empty())
                ball_groups.emplace_back();
        }
        
		// 절차 3: 찾아낸 그룹들을 하나씩 검사하여 사라지는 공을 처리
        while(!ball_groups.empty())
        {
            eraseBall(ball_groups.back());
            ball_groups.pop_back();
        }

        return total_ball_cnt != prev_cnt;
    }
    
    void printStat()
    {
        for(int l = GRID_SIZE-1;l>-1;l--)
        {
            for(int i = 0;i<GRID_SIZE;i++)
                cout<<grid[i][l]<<' ';
            cout<<endl;
        }
    }

    int total_ball_cnt;
private:
    
    vector<vector<int>> grid;

    void eraseBall(stack<int*>& ball_group)
    {
        int group_size = ball_group.size();
        while(!ball_group.empty())
        {
            int* top = ball_group.top();
            ball_group.pop();

            if(*top == group_size)
            {
                *top = 0;
                total_ball_cnt--;
            }
        }
    }

    void fallDownBall(vector<int>& col)
    {
        for(auto it = col.begin();it != col.end();)
        {
            if (*it == 0)
                it = col.erase(it);
            else 
                it++;
        }

        while(col.size() < GRID_SIZE) col.push_back(0);
    }
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int ball;
    vector<vector<int>> input(GRID_SIZE,vector<int>(GRID_SIZE));
    for(auto& row:input)
    {
        for(auto&cell:row)
            cin>>cell;
    }
    cin>>ball;

    int answer = numeric_limits<int>::max();
    for(int i = 0;i<GRID_SIZE;i++)
    {
        input[0][i] = ball;

        Drop7 drop7(input);

        while(drop7.runGameLoopOnce());
        answer = min(answer, drop7.total_ball_cnt);
        input[0][i] = 0;
    }

    cout<<answer;
    return 0;
}