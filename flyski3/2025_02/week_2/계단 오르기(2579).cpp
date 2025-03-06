#include <iostream>
#include<vector>
using namespace std;
int n;
vector<int> step;
vector<int> dp;
int main()
{
	cin>>n;
	step.resize(n);
	dp.resize(n+5);             //넉넉하게 어짜피 다 0
	for(int i=0;i<n;i++)
		cin>>step[i];
                                //dp[0]은 0
	dp[1]=step[n-2];            //2칸 or 3칸 가능
	dp[2]=step[n-3];
	dp[3]=dp[1]+step[n-4];      

	for(int i=4;i<n+5;i++)
	{
		dp[i]=min(dp[i-2],dp[i-3]);
		if(i<n)                         //n이후로 어짜피 0이긴한데 예외처리
			dp[i]+=step[n-1-i];
	}
	int sum=-dp[n+3];                   //총 합에서 빠진 계단(dp) 빼기
	for(int i=0;i<n;i++)
		sum+=step[i];
	cout<<sum;
	return 0;
}