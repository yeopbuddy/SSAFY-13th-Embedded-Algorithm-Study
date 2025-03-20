#include<iostream>
#include<algorithm>
using namespace std;
int N, H;	// N : 동굴의 길이
// H : 동굴의 높이
int bottom[100001];
int top[100001];

void init() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
}

void input() {
	cin >> N >> H;
	for (int i = 0; i < N / 2; i++)
	{
		cin >> bottom[i];
		cin >> top[i];
	}
}

int Crash(int num, int arr[]) {
	int left = 0;				// 가장 왼쪽 기준
	int right = N / 2 - 1;	// 가장 오른쪽 기준
	int mid;						// 확인할 곳

	while (left <= right) {	// 두 기준이 만날때까지 좁혀나간다
		mid = (left + right) / 2;	// 두 기준의 중간점을 확인

		if (arr[mid] < num)	// 확인한 곳이 목표수보다 작으면 오른쪽으로 가야하니까
			left = mid + 1;	// 왼쪽 기준을 확인한 곳 오른쪽으로 잡아준다
		else
			right = mid - 1;
	}

	return N / 2 - left;	// 총 개수에서 조건을 만족하는 처음 가진 인덱스를 빼주면 그보다 큰 장애물들의 개수가 나온다 = 충돌 개수
}

void solution() {
	sort(bottom, bottom + N / 2);
	sort(top, top + N / 2);

	int cnt = 0;
	int Min = 21e8;

	for (int i = 1; i <= H; i++)
	{
		int num = Crash(i, bottom) + Crash(H - i + 1, top);	// 충돌 개수 세기
		if (num < Min) {	// 현재까지의 장애물 개수보다 작으면 업데이트
			cnt = 1;
			Min = num;
		}
		else if (num == Min) {	// 아니면 카운트 추가
			cnt++;
		}
	}

	cout << Min << " " << cnt;
}

int main() {
	init();
	input();
	solution();

}