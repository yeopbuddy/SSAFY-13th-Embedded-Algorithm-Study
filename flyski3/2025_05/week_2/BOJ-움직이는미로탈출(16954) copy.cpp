/*
플러드 필 방식
몇초(st)일때 위치할 수 있는 공간 표시 -> 현재 st보다 낮은 위치는 탐색 가능
벽인 곳은 탐색x, 벽이 움직여서 충돌하면 그 위치에서 탐색x
st가 9초이상 or 벽이 더이상 없음 경우 도착 가능 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int field[8][8]={0};    //map
vector<pair<int,int>> wall;     //wall
queue<pair<int,int>> qu;        //queue
int xy[9][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1}, { 0, 0}, { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};
void mvwall()                   //벽 한칸 아래로
{
    vector<pair<int,int>> newwall;
    for (auto& li:wall) {
        field[li.first][li.second]=0;
        if(li.first<7)
        {
            newwall.push_back({li.first+1,li.second});
        }
    }
    wall=newwall;
    for (auto& li:wall) {
        field[li.first][li.second]=9;
    }
}
bool canReach()
{
    int st=1;
    qu.push({7,0});
    while(!qu.empty())
    {
        if(st>8||wall.size()==0)        //8초 or 벽 x
        {
            return true;
        }
        int size = qu.size();
        for (int j = 0; j < size; j++) {
            auto [x,y] = qu.front();
            qu.pop();
            if(field[x][y]==9)          //벽과 충돌시
            {
                continue;
            }
            for(int i=0;i<9;i++)
            {
                int dx=x+xy[i][0];
                int dy=y+xy[i][1];
                if(dx<0||dy<0||dx>=8||dy>=8)
                {
                    continue;
                }
                else if(field[dx][dy]>=st)  //같거나 벽(9)이면 탐색x
                {
                    continue;
                }
                else
                {
                    field[dx][dy]=st;
                    qu.push({dx,dy});
                }
            }
        }
        st++;
        mvwall();
    }
    return false;
}
int main()
{
    for(int i=0;i<8;i++)
    {
        string str;
        cin >> str;
        for(int j=0;j<8;j++)
        {
            if(str[j]=='#')
            {
                field[i][j]=9;
                wall.push_back({i,j});
            }
        }
    }
    cout<<canReach();
    return 0;
}
