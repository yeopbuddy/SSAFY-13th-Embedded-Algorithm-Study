#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#define endl '\n'

#include <queue>

using namespace std;

struct PowerCode
{
    int A, B;
    bool operator<(const PowerCode b) const
    {
        return this->A < b.A;
    }
};

int LIS(vector<int>& arr)
{
    int arr_len = arr.size();

    // 수열의 앞에서부터 x번째까지 고려했을 때,
    // 길이가 정확히 y인 증가하는 부분 수열 중에서
    // "최대 원소가 최소가 되도록" 선택했을 때의 그 최소값
    vector<vector<int>> DP(arr_len+1,vector<int>(arr_len+1,numeric_limits<int>::max()));
    for(int i = 0;i<=arr_len;i++)
        DP[0][i] = 0;


    for(int i = 1;i<=arr_len;i++)
    {
        for(int l = 1;l<=arr_len;l++)
        {
            if(arr[l-1] < DP[i][l-1] && arr[l-1] > DP[i-1][l-1])
                DP[i][l] = arr[l-1];
            else
                DP[i][l] = DP[i][l-1];
        }
    }

    int answer=1;
    while(answer+1 <= arr_len &&DP[answer+1][arr_len] != numeric_limits<int>::max())
        answer+=1;
    return answer;
}

int main()
{
    vector<PowerCode> input;
    
    int N;
    cin >> N;
    for(int i = 0;i<N;i++)
    {
        int a,b;
        cin >> a>> b;
        input.push_back({a,b});
    }

    sort(input.begin(), input.end(),less<PowerCode>());

    vector<int> arr;
    for(auto pc: input)
        arr.push_back(pc.B);

    cout<< N- LIS(arr);
}