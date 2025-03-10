#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
#define endl '\n'

using namespace std;

vector<pair<int,int>> move_que;

void moveTower(int start, int end, int hight)//탑이 있는 위치, 탑을 옮겨야할 위치, 탑의 높이
{
    if(hight == 1)
    {
        move_que.push_back(make_pair(start,end));
        return;
    }
    int mid = 6 - start - end; //hight-1 높이의 탑을 옮겨둘 위치
    moveTower(start,mid,hight-1);
    move_que.push_back(make_pair(start,end));//맨 밑의 원판 이동
    moveTower(mid,end,hight-1);//맨 밑의 원판 위로 hight-1탑을 옮김
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin>>N;
    moveTower(1,3,N);
    cout<<move_que.size()<<endl;
    for(auto moving:move_que)
        cout<<moving.first<<' '<<moving.second<<endl;
    return 0;
}