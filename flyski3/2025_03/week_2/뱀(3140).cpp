#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
int n, k,x,y;
int dxy[4][2]={             //방향
    -1,0,
    0,1,
    1,0,
    0,-1,
};
vector<vector<int>> board;
queue<pair<int,int>> snake;
bool move(int l)
{
    x=x+dxy[l][0];
    y=y+dxy[l][1];
    if(x>=n||y>=n||x<0||y<0||board[x][y]>1) //충돌 경우 true
        return true;
    snake.push({x,y});                      //전진
    if(board[x][y]==0)                      //사과를 먹지 않았을 경우 꼬리 pop
    {
        board[snake.front().first][snake.front().second]=0;     
        snake.pop();
    }
    board[x][y]=2;
    return false;
}
int main()
{
    fastio;
    cin >> n >> k;
    board.resize(n,vector<int>(n));
    for(int i=0;i<k;i++)
    {
        cin>>x>>y;
        board[x-1][y-1]=1;      //사과 위치 1
    }
    cin >> k;
    x=y=0;
    snake.push({0,0});          //뱀 출발
    board[x][y]=2;              //뱀이 있는 위치 2
    int start=0,end,l=1;
    char L;
    for(int i=0;i<k;i++)
    {
        cin >>end>>L;
        while(start<end)        //end초가 지나기 전까지
        {
            start++;
            if(move(l))         //충돌 경우
            {
                cout<<start;
                return 0;
            }
        }
        if(L=='D')              //D의 경우 시계방향
        {
            l+=1;
        }
        else                    //반시계방향
        {
            l-=1;
            if(l<0)             //음수일 경우 +4
            {
                l+=4;
            }
        }
        l%=4;
        
    }
    while(1)                //더이상 명령이 없을경우 무조건 직진!
    {
        start++;
        if(move(l))
        {
            cout<<start;
            return 0;
        }
    }
    return 0;
}

/*
그냥 예외처리

큐로 뱀 구현하기
x,y


방향은 %로 구현 (함수)
첫 스타트 0,0 >(1)
방향전환은 시간이 끝난 '후'

*/