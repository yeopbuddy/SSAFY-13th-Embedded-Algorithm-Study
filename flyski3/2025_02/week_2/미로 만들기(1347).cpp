#include <iostream>
#include<vector>
using namespace std;
int n;

int maxx,maxy,minx,miny;	//마지막 크기 계산용

struct miroo		
{
	int x;
	int y;
};

vector<miroo> map;			//map에 지나간 경로 벡터
vector<vector<char>> pnt;	//마지막 프린트용 벡터
vector<char> qwe;			//명령어 리스트

int step[4][2]={			//방향에 따른 f용
	-1,0,//12
	0,1,//3
	1,0,//6
	0,-1//9
};
void mro(int x,int y,int st,int idx)//0,1,2,3 * 3;
{
	if(idx>=n)
		return;
	if(qwe[idx]=='F')			//f일경우 해당 방향으로 한칸 전진
	{
		int dx=x+step[st][0];		
		int dy=y+step[st][1];
		if(maxx<dx)					//이전보다 더 멀리갈 경우 pnt의 크기를 증가시켜야함
			maxx=dx;
		else if(minx>dx)
			minx=dx;
		if(maxy<dy)
			maxy=dy;
		else if(miny>dy)
			miny=dy;
		map.push_back({dx,dy});		//.표시할 벡터
		mro(dx,dy,st,idx+1);		//다음 명령어
	}
	else if(qwe[idx]=='R')
	{
		if(st>=3)			//9시 방향일 경우 r이면 12시
			st=-1;			
		mro(x,y,st+1,idx+1);
	}
	else if(qwe[idx]=='L')
	{
		if(st<1)			//12시 방향일 경우 l이면 9시
			st=4;			
		mro(x,y,st-1,idx+1);
	}
	return;
}

int main()
{
	maxx=maxy=minx=miny=0;
	cin>>n;
	qwe.resize(n);
	for(int i=0;i<n;i++)
		cin>>qwe[i];
	map.push_back({0,0});	//스타트 지점도 지나간길
	mro(0,0,2,0);			//남쪽(6)시작
	pnt.resize(maxx-minx+1);	//마지막 프틴트용 크기계산

	for(int i=0;i<=maxx-minx;i++)
	{
		pnt[i].resize(maxy-miny+1,'#');
	}
	
	for(int i=0;i<map.size();i++)		//map에 들어있는 좌표일경우 .
	{
		pnt[map[i].x-minx][map[i].y-miny]='.';
	}

	for(int i=0;i<=maxx-minx;i++)		//프린트
	{
		for(int j=0;j<=maxy-miny;j++)
			cout<<pnt[i][j];
		cout<<endl;
	}
	return 0;
}