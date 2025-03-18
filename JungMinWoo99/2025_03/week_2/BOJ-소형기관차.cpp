#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#include <deque>

using namespace std;

int main(void)
{
    int N;
    cin >> N;
    vector<int> input(N);
    for(int idx = 0;idx<N;idx++)
        cin>> input[idx];

    //소형 기관차가 끌 수 있는 객차 수수
    int pull_cnt;
    cin>> pull_cnt;

    // idx 번째 객차부터 마지막 객차까지 주어졌을 때 소형 기관차가 최대로 끌 수 있는 객차 수
    deque<int> max_case_memorization(N - pull_cnt + 1);

    //idx~idx + pull_cnt -1 번 객차의 손님 수와 총합
    deque<int> sum_que;
    int sum = 0;
    for (int idx = N - 1; idx > N - pull_cnt - 1; idx--)
    {
        sum_que.push_front(input[idx]);
        sum += input[idx];
    }
    max_case_memorization[N - pull_cnt] = sum;

    int max_sum = sum;
    for(int idx = N - pull_cnt - 1; idx > -1 ;idx--)
    {
        sum-=sum_que.back();
        sum_que.pop_back();
        sum+=input[idx];
        sum_que.push_front(input[idx]);
        max_sum = max(sum,max_sum);
        max_case_memorization[idx] = max_sum;
    }

    // for (int ele : max_case_memorization)
    //     cout << ele << ' ';
    // cout << endl;

    // idx 번째 객차부터 마지막 객차까지 주어졌을 때 소형 기관차 2대가 최대로 끌 수 있는 객차 수
    deque<int> max_case_memorization2(N - 2 * pull_cnt + 1);
    sum_que.clear();
    sum = 0;
    for (int idx = N - pull_cnt - 1; idx > N - 2 * pull_cnt - 1; idx--)
    {
        sum_que.push_front(input[idx]);
        sum += input[idx];
    }
    max_case_memorization2[N - 2 * pull_cnt] = sum + max_case_memorization[N-pull_cnt];

    max_sum = max_case_memorization2[N - 2 * pull_cnt];
    for(int idx = N - 2 * pull_cnt - 1; idx > -1 ;idx--)
    {
        sum -= sum_que.back();
        sum_que.pop_back();
        sum += input[idx];
        sum_que.push_front(input[idx]);
        max_sum = max(max_sum, sum + max_case_memorization[idx + pull_cnt]);
        max_case_memorization2[idx] = max_sum;
    }

    // for (int ele : max_case_memorization2)
    //     cout << ele << ' ';
    // cout << endl;

    // idx 번째 객차부터 마지막 객차까지 주어졌을 때 소형 기관차 2대가 최대로 끌 수 있는 객차 수
    deque<int> max_case_memorization3(N - 3 * pull_cnt + 1);
    sum_que.clear();
    sum = 0;
    for (int idx = N - 2 * pull_cnt - 1; idx > N - 3 * pull_cnt - 1; idx--)
    {
        sum_que.push_front(input[idx]);
        sum += input[idx];
    }
    max_case_memorization3[N - 3 * pull_cnt] = sum + max_case_memorization2[N-2*pull_cnt];

    max_sum = max_case_memorization3[N - 3 * pull_cnt];
    for(int idx = N - 3 * pull_cnt - 1; idx > -1 ;idx--)
    {
        sum -= sum_que.back();
        sum_que.pop_back();
        sum += input[idx];
        sum_que.push_front(input[idx]);
        max_sum = max(max_sum, sum + max_case_memorization2[idx + pull_cnt]);
        max_case_memorization3[idx] = max_sum;
    }

    int answer = numeric_limits<int>::min();
    for(int ele:max_case_memorization3)
        answer = max(ele,answer);

    // for (int ele : max_case_memorization3)
    //     cout << ele << ' ';
    // cout << endl;

    cout<<answer<<endl;
}