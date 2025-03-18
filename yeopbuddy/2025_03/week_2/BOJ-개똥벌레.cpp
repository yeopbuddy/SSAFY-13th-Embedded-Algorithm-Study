#include <iostream>
#include <vector>
using namespace std;
int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int N, H, o; cin >> N >> H;
	vector<int> LEFT(H, 0);
	vector<int> RIGHT(H, 0);
	for (int i = 0; i < N; i++) {
		cin >> o;
		if (i % 2 == 0) {
			LEFT[o - 1]++;
		}
		else {
			RIGHT[H - o]++;
		}
	}
	// LEFT, RIGHT 누적합 연산
	for (int i = H - 2; i >= 0; i--) {
		LEFT[i] += LEFT[i + 1];
		RIGHT[H - i - 1] += RIGHT[H - i - 2];
	}
	int MINVAL = LEFT[0] + RIGHT[0]; int MINCNT = 1;
	for (int i = 1; i < H; i++) { // min 값과 개수 찾기
		if (MINVAL == LEFT[i] + RIGHT[i]) {
			MINCNT++;
		}
		else if (MINVAL > LEFT[i] + RIGHT[i]) { // init 
			MINVAL = LEFT[i] + RIGHT[i];
			MINCNT = 1; 
		}
	}
	cout << MINVAL << " " << MINCNT;
}