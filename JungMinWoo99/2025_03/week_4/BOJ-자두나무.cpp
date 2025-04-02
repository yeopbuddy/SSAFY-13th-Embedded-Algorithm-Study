#include <iostream>
#include <cstring>
#define endl '\n';

#include <vector>
#include <deque>

#define MAX_T 1000
#define MAX_W 30
#define MAX_TREE 2
using namespace std;

/*
DP[t][w][tree]: t초에 w번 이동한 상황에서 받아먹은 자두의 최댓값
DP[t][w][tree] = max(DP[T-1][w][tree], DP[T-1][w-1]][!tree]);
*/

int DP[MAX_T+1][MAX_W+1][MAX_TREE] = {-1,};
vector<int> input;

int getDP(int time, int w, int tree)
{
    if(time ==0)
    {
        if(tree == 0)//1번 트리 시작하는 경우
            return 0;
        else//2번 트리 시작하는 경우
            return -MAX_T;//문제에서 무조건 1번부터 시작한다 했으므로 2번부터 시작하는 경우를 무조건 배제
    }
    else if(DP[time][w][tree] != -1)
        return DP[time][w][tree];
    
    if(w==0)
        DP[time][w][tree] = getDP(time-1,w,tree) + ((input[time]-1) == tree);
    else
        DP[time][w][tree] = max(getDP(time-1,w,tree),getDP(time-1,w-1,!tree)) + ((input[time]-1) == tree);
    return DP[time][w][tree];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(DP, -1, sizeof(DP));

    int T, W;
    cin >> T >> W;
    input.push_back(0);
    for (int i = 0; i < T; i++)
    {
        int in;
        cin>> in;
        input.push_back(in);
    }

    cout<<max(getDP(T,W,0),getDP(T,W,1))<<endl;

    return 0;
}