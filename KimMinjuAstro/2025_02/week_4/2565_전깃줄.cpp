#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int N;
//int sequence[1001];
int DP[501];
struct line
{
	int a;
	int b;

	bool operator<(line right) {
		return a < right.a;
	}
};
vector<line>lines;
int LIS() {

	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		DP[i] = 1;
		for (int j = i - 1; j >= 0; j--)
		{
			if (lines[i].b > lines[j].b) {
				DP[i] = max(DP[i], DP[j] + 1);
			}
		}
		cnt = max(DP[i], cnt);
	}
	return cnt;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		lines.push_back({ a,b });
	}

	sort(lines.begin(), lines.end());

	cout << N - LIS();
}