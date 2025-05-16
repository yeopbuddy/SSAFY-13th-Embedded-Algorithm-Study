#include <iostream>
#define endl '\n'

#include <algorithm>
#include <cctype>
#include <limits>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Scheduler
{
   public:
    Scheduler(int N) : N(N), prev_work_cnt(N + 1, 0), next_work_list(N + 1), work_time(N + 1),work_start(N+1,0)
    {
        for (int idx = 1; idx <= N; idx++)
        {
            int b;
            cin >> work_time[idx] >> b;
            for (int cnt = 0; cnt < b; cnt++)
            {
                int prev_work;
                cin >> prev_work;
                next_work_list[prev_work].push_back(idx);
                prev_work_cnt[idx]++;
            }
        }
    }

    int TopologicalSort()
    {
        int end_time = 0;
        queue<pair<int, int>> search_que;  // 작업번호, 시작 시간
        for (int idx = 0; idx <= N; idx++)
        {
            if (prev_work_cnt[idx] == 0) search_que.push({idx, 0});
        }

        while (!search_que.empty())
        {
            auto cur_work = search_que.front();
            search_que.pop();
            int cur_work_end = cur_work.second + work_time[cur_work.first];
            end_time = max(end_time, cur_work_end);
            for(auto next_work: next_work_list[cur_work.first])
            {
                prev_work_cnt[next_work]--;
                work_start[next_work] = max(work_start[next_work],cur_work_end);
                if(prev_work_cnt[next_work] == 0)
                    search_que.push({next_work,work_start[next_work]});
            }
        }

        return end_time;
    }

   private:
    int N;
    vector<vector<int>> next_work_list;
    vector<int> prev_work_cnt;
    vector<int> work_time;
    vector<int> work_start;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    Scheduler scheduler(N);
    cout<<scheduler.TopologicalSort();

    return 0;
}