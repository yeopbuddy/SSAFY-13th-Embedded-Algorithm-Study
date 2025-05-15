#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*
선행 작업 중 최대값 + 자신의 작업시간 배열
*/
int main()
{
    int list[10001],N,maxval=0;
    cin >> N;
    list[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        int time, pre, val = 0;
        cin >> time >> pre;
        for (int j = 0; j < pre; j++)
        {
            int tep;
            cin >> tep;
            val = max(val, list[tep]);
        }
        list[i] = val + time;
        maxval=max(maxval,list[i]);
    }
    cout<<maxval;
    return 0;
}