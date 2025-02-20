#include <iostream>
using namespace std;

int main()
{
	int start, end;
	cin >> start >> end;

	// i : 소수인지 판별하려는 수
	for (int i = start; i <= end; ++i)
	{
		int flag = 0;
		// j : 약수인지 판별
		for (int j = 2; j * j <= i; ++j)
		{
			if (i % j == 0)
			{
				flag = 1; // 합성수
				break;
			}
		}
		// 1 제외
		if (i != 1)
		{
			if (flag == 0)	// 소수
			{
				cout << i << "\n";
			}
		}
	}

	return 0;
}