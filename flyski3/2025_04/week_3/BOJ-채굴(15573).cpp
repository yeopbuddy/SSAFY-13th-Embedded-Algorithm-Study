#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
다이스트라
강도가 높아서 채굴하지 못한 위치와 필요한 레벨로 pq
채굴 성공시 해당 카운트 증가
해당 큐에서 종료조건 만족시 해당 큐의 강도 리턴
방문처리는 10^7
bfs용이하게 겉 테두리 0설정 > 테두리를 한번 bfs돌면 가장자리의 강도 확인가능
*/

struct Node {
    int x, y;
    int level;
    bool operator<(const Node& other) const {
        return level > other.level;
    }
};

int dxy[4][2]={
    -1,0,
    0,1,
    1,0,
    0,-1
};
int bfs(vector<vector<int>>& mineral,int N,int M,int K)
{
    priority_queue<Node> minning;
    minning.push({0,0,0});                              //시작위치 0,0 왼쪽위 테두리
    mineral[0][0]=10000000;
    int cont=0;
    while(!minning.empty())
    {
        Node n=minning.top();
        minning.pop();
        for(int i=0;i<4;i++)
        {
            int dx=n.x+dxy[i][0];
            int dy=n.y+dxy[i][1];
            if(dx<0||dy<0||dx>N||dy>M+1)                //예외처리
            {
                continue;
            }
            else if(mineral[dx][dy]==10000000)          //방문처리
            {
                continue;
            }
            else if(mineral[dx][dy]>n.level)            //강도 부족시 필요한 강도로 pq
            {
                minning.push({n.x,n.y,mineral[dx][dy]});
            }
            else
            {
                if(dx>=1&&dy>=1&&dy<=M)                 //테두리 제외 채굴시
                    cont++;
                mineral[dx][dy]=10000000;
                minning.push({dx,dy,n.level});
            }
        }
        if (cont >= K) {
            return n.level;
        }
    }
    return -1;
}
int main()
{
    int N,M,K,sum=0;
    cin >> N>>M>>K;
    int idx=1,temp;
    vector<vector<int>> mineral(N+1,vector<int>(M+2,0));//bfs용 테두리
    
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            cin >> mineral[i][j];
        }
    }
    cout<<bfs(mineral,N,M,K);
    return 0;
}
