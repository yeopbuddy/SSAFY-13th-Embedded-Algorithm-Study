#include <iostream>
#include <vector>
using namespace std;
/*
    목표는 자신턴에 n,m에 도달하여 게임을 이기는 것
    = 상대턴에 도달하지 못하도록 막는 것
    맨 아래와 오른쪽은 오른쪽과 아래로 한칸만 움직일 수 있기 때문에 결과가 정해져 있음
    
    내가 움직였을 때
    그 칸부터 시작한 상대가 결과가 승리로 정해진 위치로 가면 패배 = L로 표시 (W와 연결되어 있는 위치)
    L만 갈 수 있는 위치에서 상대가 시작하게 된다면 상대는 L로 갈 수 밖에 없다! = W로 표시 (w가 없는 위치)

    이 조건을 가지고 게임판을 채운다음
    현재 위치에서 W가 적힌 위치로 갈 수 있다면 승리
    아니면 패배
*/
int n,m,k,ex;
char input;
vector<vector<int>> game;
bool WL(int x,int y)                //W가 있다면 false / 없다면 true
{
    if(game[x+1][y]==1||game[x][y+1]==1)
    {
        return false;
    }
    int i=1;
    while(k+1-i)
    {
        if(game[x+i][y+i]==1)
            return false;
        i++;
    }
    return true;
}
int main() {
    cin>>n>>m>>k;
    game.resize(n+k+1,vector<int>(m+k+1,9));    //예외 처리(대각선)
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>input;
            if(input!='#')                      //벽이 아니라면 0 / 벽이면 9
            {
                game[i][j]=0;
            }
        }
    }
    for(int i=n-1;i>=0;i--)
    {
        for(int j=m-1;j>=0;j--)
        {
            if(game[i][j]==9)
            {
                continue;
            }
            game[i][j]=WL(i,j);                     //W= 1,L=0
            if(i==n-1&&j==m-1)
            {
                game[i][j]=1;
            }
        }
    }
    cin >> ex;
    for(int i=0;i<ex;i++)
    {
        cin>>n>>m;
        if(!WL(n-1,m-1))                        // W로 갈 수 있다면
        {
            cout<<"First\n";
        }
        else
        {
            cout<<"Second\n";
        }
    }
    return 0;
}