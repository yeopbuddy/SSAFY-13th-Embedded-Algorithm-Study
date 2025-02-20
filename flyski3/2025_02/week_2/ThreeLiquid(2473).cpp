#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n;
vector<long long> liq;
int main()
{
	cin >>n;
	liq.resize(n);
	for(int i=0;i<n;i++)
		cin>>liq[i];
	sort(liq.begin(),liq.end());
	long long minn = 3000000001;                    // 하나당 10000000000 
	vector<long long> qwe(3);
	for(int i=0;i<n-2;i++)
	{
		
		int idx=i+1;
		int idy=n-1;
		while(idx<idy)
		{
			long long sum=liq[i]+liq[idx]+liq[idy];     //세 용액 합
			if(minn>abs(sum))
			{
				minn=abs(sum);                          //절대값이 최소치인경우 교체후 기록
				qwe[0]=liq[i];
				qwe[1]=liq[idx];
				qwe[2]=liq[idy];
			}
			if(sum==0)
			{
				cout<<liq[i]<<" "<<liq[idx]<<" "<<liq[idy];
				return 0;
			}
			else if(sum>0)
			{
				idy--;

			}
			else
			{
				idx++;
			}
		}
	}
	cout<<qwe[0]<<" "<<qwe[1]<<" "<<qwe[2];
	return 0;
}