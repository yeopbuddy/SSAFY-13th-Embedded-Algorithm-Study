#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int N;
int dxy[4][2]={
    -1,0,
    0,1,
    1,0,
    0,-1
};
bool vist[3][3]={false};
char line[9];
bool chk=false;
vector<int> path;
void dfs(int x,int y,int sum,int M,int st) //1이면 + -1이면 - 0이면 +/-
{
    if(M<=0||chk)
    {
        if(sum==N)
        {
            chk=true;
        }
        return;
    }
    
    for(int i=0;i<4;i++)
    {
        int dx=x+dxy[i][0];
        int dy=y+dxy[i][1];
        if(dx<0||dy<0||dx>=3||dy>=3||vist[dx][dy])
        {
            continue;
        }
        vist[dx][dy]=true;
        int temp =3*dx+dy;
        if(st==1)
        {
            dfs(dx,dy,sum+(line[temp]-'0'),M-1,0);
        }
        else if(st==-1)
        {
            dfs(dx,dy,sum-(line[temp]-'0'),M-1,0);
        }
        else
        {
            if(line[temp]=='+')
            {
                dfs(dx,dy,sum,M,1);
            }
            else
            {
                dfs(dx,dy,sum,M,-1);
            }
        }
        if(chk)
        {
            path.push_back(temp);
            return;
        }
        vist[dx][dy]=false;
    }
    return;
}
int main()
{
    int M;
    cin>>N>>M;
    
    for (int i = 0; i < 9; i++)
    {
        cin>>line[i];
    }
    for(int i=0;i<9;i+=2)
    {
        int x =i/3;
        int y =i%3;
        vist[x][y]=true;
        dfs(x,y,line[i]-'0',M-1,0);
        if(chk)
        {
            path.push_back(i);
            break;
        }
        vist[x][y]=false;
    }
    if(!chk)
    {
        cout<<"0";
    }
    else
    {
        cout<<"1"<<endl;
        while (!path.empty()) {
            int li = path.back();
            cout << li / 3 << " " << li % 3 << endl;
            path.pop_back();
        }

    }
    return 0;
}
