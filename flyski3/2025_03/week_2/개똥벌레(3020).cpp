#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
int n, h;
int main()
{
    fastio;
    cin >> n >> h;
    vector<int> destroy[2];
    destroy[0].resize(h, 0);    //홀수번째 수
    destroy[1].resize(h, 0);    //짝수번째 수
    int x;
    int miny = 200000;

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        x--;
        destroy[i % 2][x]++;
    }
    for (int j = h-2; j >=0; j--)       //j번째 높이인 개수
    {
        destroy[0][j]+=destroy[0][j+1];
        destroy[1][j]+=destroy[1][j+1];
    }
    x=0;
    for (int j = 0; j <h; j++)
    {
        destroy[0][j]+=destroy[1][h-1-j];   //결합
        if(destroy[0][j]<miny)              //만약 적은수가 나오면
        {
            miny=destroy[0][j];
            x=1;
        }
        else if(destroy[0][j]==miny)
        {
            x++;
        }
    }

    cout << miny<< " " << x;
    return 0;
}