#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#define endl '\n'

#include <queue>

using namespace std;

pair<int,int> getTopTwo(vector<int>& arr)
{
    pair<int,int> top_two = {numeric_limits<int>::min(),numeric_limits<int>::min()};
    pair<int,int> top_two_idx = {numeric_limits<int>::min(),numeric_limits<int>::min()};
    for(int i = 0;i<arr.size();i++)
    {
        if(arr[i] > top_two.first)
        {
            top_two.second = top_two.first;
            top_two.first = arr[i];
            top_two_idx.second= top_two_idx.first;
            top_two_idx.first = i;
        }
        else if(arr[i] > top_two.second)
        {
            top_two.second = arr[i];
            top_two_idx.second = i;
        }
    }

    return top_two_idx;
}

int main()
{
    int N, K;
    cin >> N >> K;
    vector<vector<int>> input(N, vector<int>(K));
    for (int i = 0; i < N; i++)
    {
        for (int l = 0; l < K; l++)
            cin >> input[i][l];
    }

    vector<vector<int>> DP(N, vector<int>(K));
    for (int l = 0; l < K; l++)
        DP[0][l] = input[0][l];
    
    for(int i = 1;i<N;i++)
    {
        auto top_two = getTopTwo(DP[i-1]);
        for (int l = 0; l < K; l++)
            if (top_two.first != l)
                DP[i][l] = DP[i - 1][top_two.first] + input[i][l];
            else
                DP[i][l] = DP[i - 1][top_two.second] + input[i][l];
    }

    auto top_two = getTopTwo(DP[N-1]);
    cout<<DP[N-1][top_two.first];

    return 0;
}