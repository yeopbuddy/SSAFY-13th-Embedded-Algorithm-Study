/*
DP[x][y]: x번째 카드부터 y번째 카드가 남아있는 상황에서부터 선공이 얻을 수 있는 최대 점수
DP[x][y]: sum(x~y) - min(DP[x+1][y],DP[x][y-1])
    => x~y번째 카드가 남아있는 상태에서 
    선공은 x+1~y번째 카드가 남아있는 상태 또는 x~y-1번째 카드가 남아있는 상태를 후공에게 넘길 수 있음
        => 선공은 후공이 최소한의 점수를 얻을 수 있는 경우의 수를 넘겨줌 
*/
#include <iostream>
#define endl '\n'

#include <vector>
#include <algorithm>
#include <cctype>
#include <numeric>

using namespace std;

using Range = pair<int,int>; 

class CardGame
{
public:
    void InputTestCase(int N)
    {
        input_size = N;
        input.push_back(0);
        suffix_sum.push_back(0);
        for(int i = 0;i<N;i++)
        {
            int a;
            cin >> a;
            input.push_back(a);
            suffix_sum.push_back(suffix_sum.back()+a);
        }
        DP.resize(N+1,vector<int>(N+1,0));
        visited.resize(N+1,vector<int>(N+1,false));

        for(int idx = 0;idx<=N;idx++)
        {
            DP[idx][idx] = input[idx];
            visited[idx][idx]=true;
        }
    }

    int FillDP(Range pos)
    {
        if(!visited[pos.first][pos.second])
        {
            int range_sum = suffix_sum[pos.second] - suffix_sum[pos.first-1];
            int take_left_case = FillDP({pos.first + 1, pos.second});
            int take_right_case = FillDP({pos.first, pos.second - 1});

            DP[pos.first][pos.second] = range_sum - min(take_left_case, take_right_case);
            visited[pos.first][pos.second] = true;
        }
        return DP[pos.first][pos.second];
        
    }

private:
    int input_size;
    vector<int> input;
    vector<int> suffix_sum;
    vector<vector<int>> DP;
    vector<vector<int>> visited;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    for(int tc =0;tc<T;tc++)
    {
        int N;
        cin>>N;
        CardGame card_game;
        card_game.InputTestCase(N);
        int answer = card_game.FillDP({1,N});
        cout<<answer<<endl;
    }

    return 0;
}