#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
int main()
{
	cin >>n>>m;
	vector<int> q(m+1,1);           //소수 식 사용
	q[0]=q[1]=0;        
	for(int i=2;i*i<=m;i++)
	{
		if(q[i])
		{
			for(int j=i*i;j<=m;j+=i)
				q[j]=0;
		}
	}
	for(int i=n;i<=m;i++)
	{
		if(q[i])
			cout<<i<<endl;
	}
	return 0;
}