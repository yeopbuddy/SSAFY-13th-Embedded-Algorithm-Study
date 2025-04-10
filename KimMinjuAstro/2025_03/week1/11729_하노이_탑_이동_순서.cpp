#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int K;

// 원판 이동 함수
void HanoiTop(int n, int start, int mid, int end) {
	if (n == 1) {
		cout << start << " " << end << "\n";
	}
	else
	{
		// n-1개의 원판을 처음에서 끝을 거쳐 중간에 놓고
		HanoiTop(n - 1, start, end, mid);

		// 가장 아래쪽의 원판을 끝에 놓는다
		cout << start << " " << end << "\n";

		// 중간에 놨던 n-1개의 원판을 처음을 거쳐 끝에 놓는다
		HanoiTop(n - 1, mid, start, end);
	}
}

int main() {
	cin >> K;
	// int로 명시해줘야 답이 맞음. 백준 이상해
	cout << (int)(pow(2, K) - 1) << "\n";
	HanoiTop(K, 1, 2, 3);
}
