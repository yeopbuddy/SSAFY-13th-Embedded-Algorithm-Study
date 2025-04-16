/*
어차피 총 점수가 높은 게 장땡이니 1시간에 얼마나 up 되는지가 중요
우선 순위 큐에다 다 집어넣고 up효율이 높은 것을 꺼내 총 점수에 더해주고 final 점수를 갱신시켜 다시 큐에 넣어준다
예외처리 해야할 것은 up됐을 때 100점 초과로 나오면 up 효율이 최대가 아닌 것이니 up을 바꿔주고 큐에 넣어준 뒤 없던 일인척 한다
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;
int hour, subCnt;	// n : 24 X n 시간이 주어짐
					// m : 과목 개수
int sum;
struct Subject
{
	int base;
	int up;
	int final;

	bool operator<(Subject right)const {
		
		if (up < right.up)return true;
		if (up > right.up)return false;

		if (final > right.final)return true;
		if (final < right.final)return false;

		return false;
	}
};


priority_queue<Subject>pq;
int main() {
	cin >> hour >> subCnt;
	vector<Subject>subjects(subCnt);
	for (int i = 0; i < subCnt; i++)
	{
		cin >> subjects[i].base;
		subjects[i].final = subjects[i].base;
		sum += subjects[i].base;
	}
	for (int i = 0; i < subCnt; i++)
	{
		cin >> subjects[i].up;
	}
	for (int i = 0; i < subCnt; i++)
	{
		Subject sub = subjects[i];
		pq.push({ sub.base, sub.up, sub.final });
	}

	for (int h = 0; h < hour * 24; h++)
	{
		Subject sub = pq.top(); pq.pop();
		if (sub.final + sub.up > 100) {
			sub.up = 100 - sub.final;
			pq.push(sub);
			h--;
			continue;
		}
		else {
			sum += sub.up;
			sub.final += sub.up;
			pq.push(sub);
		}
	}

	cout << sum;
}