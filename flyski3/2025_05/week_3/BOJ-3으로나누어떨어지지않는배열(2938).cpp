#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void chk(queue<int> (&list)[3], vector<int> &solve)
{
    int siz[3];
    for (int i = 0; i < 3; i++)
        siz[i] = list[i].size();
    if ((siz[1] > 0 && siz[2] > 0 && siz[0] == 0) || (siz[1] + siz[2] + 1 < siz[0])) // 1+2,0+0 발생
    {
        solve.push_back(-1);
        return;
    }

    for (int i = 0; i < siz[1]; i++) // 1배열
    {
        if (siz[0] >= 2) // 만약 0이 2개 이상이면
        {
            solve.push_back(list[0].front());
            list[0].pop();
            siz[0]--;
        }
        solve.push_back(list[1].front());
        list[1].pop();
    }
    if (siz[0] > 0) // 1과2사이 0
    {
        solve.push_back(list[0].front());
        list[0].pop();
        siz[0]--;
    }
    for (int i = 0; i < siz[2]; i++) // 2배열
    {
        solve.push_back(list[2].front());
        list[2].pop();
        if (siz[0] > 0) // 만약 0이 2개 이상이면
        {
            solve.push_back(list[0].front());
            list[0].pop();
            siz[0]--;
        }
    }
    return;
}
int main()
{
    queue<int> list[3];
    vector<int> solve;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        list[temp % 3].push(temp);
    }
    chk(list, solve);
    for (auto li : solve)
    {
        cout << li << " ";
    }
    return 0;
}
/*
%3으로 값에 따라 저장

1-2 사이 0이 필요
0-0 사이 1,2 필요

1과 2가 많은건 상관없음
1과 2가 있다면 0은 1개이상 필요
0의 개수<=1의개수+2의개수+1이 필요
*/