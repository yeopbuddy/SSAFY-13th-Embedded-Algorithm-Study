#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <numeric>

using namespace std;

class TeamMaker{
public:
    TeamMaker(int n): N(n),DP(N+1,vector<int>(N,0)),interval_score(N+1,vector<int>(N,-1)){
        for(int idx = 0;idx<N;idx++){
            int in;
            cin >> in;
            input.push_back(in);
        }
    }

    void FillIntervalScore(){
        for(int team_size = 1; team_size<= N;team_size++)
            for(int idx = 0; idx <= N - team_size;idx++)
                interval_score[team_size][idx] = *max_element(input.begin()+idx,input.begin()+idx+team_size) - *min_element(input.begin()+idx,input.begin()+idx+team_size);
    }

    //시간복잡도가 O(N^3)이 아닌 O(N^2)이 되는 이유에 대해 생각해보기
    void FillDP(){
        for(int team_size = 1; team_size<= N;team_size++){
            for(int idx = 0; idx <= N - team_size;idx++){
                DP[team_size][idx] = interval_score[team_size][idx];
                for(int div_team = 1;div_team<team_size;div_team++){
                    int score = DP[div_team][idx] + DP[team_size-div_team][idx+div_team];
                    DP[team_size][idx] = max(score, DP[team_size][idx]);
                }
            }
        }
    }

    void PrintAnswer(){
        cout<< DP[N][0]<<endl;
    }
private:
    int N;
    vector<int> input;
    vector<vector<int>> interval_score;
    vector<vector<int>> DP;//DP[i][j] : j번째 인원부터 i명이 팀을 이룬 경우 가치
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    TeamMaker tm(N);
    tm.FillIntervalScore();
    tm.FillDP();
    tm.PrintAnswer();

    return 0;
}