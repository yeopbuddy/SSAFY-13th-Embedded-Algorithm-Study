#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;

struct ct
{
    long long sum = 0;
    int idx;
    /* data */
};
bool cmp(ct &a, ct &b)
{
    if (a.sum == b.sum)
    {
        return a.idx < b.idx;
    }
    return a.sum > b.sum;
}
ct cat[3] = {0}; // max 2개 값,인덱스
ct prv[2] = {0};
int main()
{
    fastio;
    int n, k;
    cin >> n >> k;
    int x;
    for (int j = 0; j < k; j++)             //현재까지 쌓인 값중 max2개
    {
        cin >> x;
        if (x > prv[1].sum)
        {
            if (x > prv[0].sum)
            {
                prv[1].sum = prv[0].sum;
                prv[1].idx = prv[0].idx;
                prv[0].sum = x;
                prv[0].idx = j;
            }
            else
            {
                prv[1].sum = x;
                prv[1].idx = j;
            }
        }
    }
    // cout << prv[0].idx << " " << prv[0].sum << endl;
    // cout << prv[1].idx << " " << prv[1].sum << endl;

    for (int i = 1; i < n; i++)                 //max3개를 뽑기기
    {
        cat[0].sum = cat[1].sum = cat[2].sum =0;
        for (int j = 0; j < k; j++)
        {
            cin >> x;
            if (x > cat[2].sum)
            {
                if (x > cat[1].sum)
                {
                    if (x > cat[0].sum)
                    {
                        cat[2].sum = cat[1].sum;
                        cat[2].idx = cat[1].idx;
                        cat[1].sum = cat[0].sum;
                        cat[1].idx = cat[0].idx;
                        cat[0].sum = x;
                        cat[0].idx = j;
                    }
                    else
                    {
                        cat[2].sum = cat[1].sum;
                        cat[2].idx = cat[1].idx;
                        cat[1].sum = x;
                        cat[1].idx = j;
                    }
                }
                else
                {
                    cat[2].sum = x;
                    cat[2].idx = j;
                }
            }
        }
        // cout<<cat[0].sum<<" "<<cat[1].sum<<" "<<cat[2].sum<<endl;
        if (cat[0].idx == prv[0].idx)           //만약 max(0)의 값이 뽑은것중 가장 큰수의 인덱스와 같다면
        {                                       //max(1)+가장큰수와 max(0)+3번째 큰수와 비교
            prv[1].sum += cat[0].sum;
            if(prv[0].sum+cat[2].sum>prv[1].sum) 
            {
                prv[1].sum=prv[0].sum+cat[2].sum;
                prv[1].idx = cat[2].idx;
            }
            else
            {
                prv[1].idx = cat[0].idx;
            }
            prv[0].sum += cat[1].sum;           //max(0)+2번째 수
            prv[0].idx = cat[1].idx;
        }
        else if (cat[1].idx == prv[0].idx)      //max(0)과 2번째 큰수의 인덱스가 같다면
        {
            prv[1].sum += cat[1].sum;
            if(prv[0].sum+cat[2].sum>prv[1].sum)    //max(1)+2번째 수와 max(0)+3번째 수와 비교
            {
                prv[1].sum=prv[0].sum+cat[2].sum;
                prv[1].idx = cat[2].idx;
            }
            else
            {
                prv[1].idx = cat[1].idx;
            }
            prv[0].sum += cat[0].sum;                   //max(0)과 큰수
            prv[0].idx = cat[0].idx;
        }
        else
        {
            prv[1].sum = prv[0].sum + cat[1].sum;       //아니면 크로스
            prv[1].idx = cat[1].idx;
            prv[0].sum += cat[0].sum;
            prv[0].idx = cat[0].idx;
        }
        sort(prv, prv + 2, cmp);
        // cout << prv[0].idx << " " << prv[0].sum << endl;
        // cout << prv[1].idx << " " << prv[1].sum << endl;
    }

    cout << prv[0].sum;
    return 0;
}
/*
3 6
10 20 20 10 10 10
10 30 10 10 10 10
10 40 10 10 10 10
out:70

3 3
10 20 30
30 20 10
20 30 10
out:90

3 3
10 20 30
10 20 40
10 20 20
out:80

5 5
30 1 1 1 1
40 1 1 1 1
60 1 1 1 1
60 1 1 1 1
60 1 1 1 1
out:152

1 6
70 1 1 1 1 1
out:70

4 3
30 40 1
40 30 1
0 50 40
70 0 70
out:200

3 5
1000 1 5 1 1
4 2 3 1 1
1000 1 5 1 1
out: 2003
*/