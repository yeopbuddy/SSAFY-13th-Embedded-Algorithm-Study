#include <iostream>
#include <vector>
#include <algorithm>
#define fastio ios::sync_with_stdio(0);cin.tie(0);
using namespace std;
struct space
{
	long long val=1;		//값
	int idx;				//주소인덱스
};
int n, m;
vector<space> sp;           //값과 참조idx담은 벡터
vector<string> prin;        //출력값 저장벡터
long long sum = 0;
int con = 0;

int gcd(long long a, int b)             //최대공약수 함수
{
	while (b != 0)
	{
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

void pri()                                  //나온 값 string 제작해서 저장
{
	int div = (n - con);
	long long temp = gcd(sum, div);
	string str;
	str=to_string(sum / temp)+"/"+to_string(div / temp);
	prin.push_back(str);
	return;
}

int main()
{
	fastio;
	cin >> n >> m;
	sp.resize(n);
	for(int i=0;i<n;i++)
		sp[i].idx=i;

	sum = n;
	int k, x, y;
	for (int q = 0; q < m; q++)
	{
		cin >> k;
		if (k == 2)                         //2일경우 pri();
		{
			pri();
		}
		else
		{
			cin >> x >> y;
			x--;
			y--;
			if (sp[x].val == 0)         // 이미 다른곳에서 더해서 비워진 벡터이면
			{
				int id=sp[x].idx;
				while (sp[id].val == 0)         // 만약 이 위치도 비워진 벡터이면
				{
					id=sp[id].idx;              // 또 그 값을 받아간 위치
				}
				sp[x].idx=id;
			}
			if (sp[y].val == 0)
			{
				int id=sp[y].idx;
				while (sp[id].val == 0) 
				{
					id=sp[id].idx;
				}
				sp[y].idx=id;
			}

			x=sp[x].idx;                            //x,y는 값을 가지고 있는 위치
			y=sp[y].idx;
			if(x==y)                                //두 위치가 같으면 건너뛰기
				continue;
			sum -= (sp[x].val * sp[x].val) + (sp[y].val * sp[y].val);
			sp[x].val+=sp[y].val;
			sum += sp[x].val * sp[x].val;
			sp[y].val=0;
			sp[y].idx=x;                            //값을 더한 후 idx저장장
			con++;
		}
	}
	for(int i=0;i<prin.size();i++)
	{
		cout<<prin[i]<<endl;
	}
	return 0;
}
/*
1=1/1
각 정점당 val=1;
그룹수 n;
2개가 합쳐지면
n--; 합쳐진 정점 val1+val2
나머지 위치는 0으로
*/
// 1 1 1 1 1 1 1sum=7;
// 2 0 1 1 1 1 1sum=7-1-1+4=9;
// 3 0 0 1 1 1 1sum=9-4-1+9=13;