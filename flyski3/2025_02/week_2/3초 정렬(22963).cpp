#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);  // I/O 성능 향상
	cin.tie(NULL);
	int n;
	vector<int> b;
	vector<int> idx;
	cin >> n;
	b.resize(n+1);
	b[0] = 1;
	for (int i = 1;i <= n;i++)
		cin >> b[i];

	for (int i = 1;i < n;i++)
	{
		if (b[i] > b[i + 1])                        // !(<=)경우 바꿔야 할 위치 idx기록
		{                                           // 오름차순에서 오류 발생
			int left = 0;
			int right = 1;
			while (i > left)
			{
				if (b[i + 1] >= b[i - left])        //왼쪽부터 하나씩 삭제할경우 오름차순이 가능한 위치
					break;
				left++;
			}
			while (right < n+1- i)
			{
				if (b[i] <= b[i +right])             //오른쪽부터 하나씩 삭제할 경우 오름차순이 가능한 위치
					break;
				right++;
			}
			if (left <= right-1)                       //비교해서 적은수 idx기록
			{
				for (int j = 0;j < left;j++)
				{
					idx.push_back(i - j);
				}
			}
			else
			{
				for (int j = 1;j < right;j++)
				{
					idx.push_back(i + j);
				}
			}						// 0 1 2 3 4 5 6 7 8 9  n=9;
		}							// 1 2 3 1 1 1 4 5 6 7  3>1 & not (1 >= 2) >>else 1>3 1>3 1>3
									// 1 2 3 9 9 9 4 5 6 7  9>4 & not (4 >= 9) >>else 4>9 5>9 6>9 7>9 not!!
									// 1 2 3 9 9 9 4 5 9 9  9>4 & not (4 >= 9) >>else 4>9 5>9
			
	}
	sort(idx.begin(), idx.end());                       //중복 기록된 idx 삭제
	auto it = unique(idx.begin(), idx.end());
	idx.erase(it, idx.end());

	for (int i = 0;i < idx.size();i++)                  //정상적으로 교체
	{
		b[idx[i]] = b[idx[i] - 1];
	}
	
	if (idx.size() > 3) // 3개이상일경우 무조건 NO
	{
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	cout << idx.size() << endl;
	for (int i = 0;i < idx.size();i++)
	{
		cout << idx[i] << " " << b[idx[i]] << endl;
	}
	return 0;
}