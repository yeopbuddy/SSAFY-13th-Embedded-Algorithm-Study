#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define endl '\n'

using namespace std;

/*
문제 해설
interval 번째 구간을 지나는 경우
높이가 interval이상인 석순, 높이가 N-interval+1이상인 종유석을 파괴
    => 석순과 종유석을 정렬하고 이진 탐색을 통해 해당 높이 이상의 값을 카운팅
*/

// 이진 탐색을 통해 threshold와 같거나 큰 가장 작은 값의 인덱스를 탐색
int countAboveThreshold(const vector<int> &sorted_vector, int thr)
{
    int start = 0;
    int end = sorted_vector.size();
    int mid;

    while (end != start)
    {
        mid = (start + end) / 2;
        if (sorted_vector[mid] < thr)
            start = mid + 1;
        else
            end = mid;
    }

    return sorted_vector.size() - end;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, H;
    cin >> N >> H;

    vector<int> stalagmites; // 석순
    vector<int> stalactites; // 종유석

    for (int idx = 0; idx < N; idx++)
    {
        int input;
        cin >> input;
        if (idx % 2 == 0)
            stalagmites.push_back(input);
        else
            stalactites.push_back(input);
    }

    sort(stalagmites.begin(), stalagmites.end());
    sort(stalactites.begin(), stalactites.end());

    int min_val = numeric_limits<int>::max();
    int min_cnt = 1;
    for (int interval = 1; interval <= H; interval++)
    {
        int destroy_cnt = countAboveThreshold(stalagmites, interval) + countAboveThreshold(stalactites, H-interval+1);
        if(min_val > destroy_cnt)
        {
            min_val = destroy_cnt;
            min_cnt = 1;
        }
        else if(min_val == destroy_cnt)
            min_cnt++; 
    }

    cout<<min_val<<' '<<min_cnt;
    return 0;
}