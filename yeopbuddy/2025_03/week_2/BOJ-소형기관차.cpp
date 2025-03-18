#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
	int n; cin >> n; vector<int>TRAIN(n);
	for (int i = 0; i < n; i++) {
		cin >> TRAIN[i];
	}
	int nn; cin >> nn; int newsize = n - nn + 1;
	vector<int>SUBTRAIN(newsize);
	int initSlidingWindow = 0;
	for (int i = 0; i < nn; i++) {
		initSlidingWindow += TRAIN[i];
	}
	// set subtrain
	SUBTRAIN[0] = initSlidingWindow;
	for (int i = 1; i < newsize; i++) {
		initSlidingWindow -= TRAIN[i-1];
		initSlidingWindow += TRAIN[i+nn-1];
		SUBTRAIN[i] = initSlidingWindow;
	}
	vector<int>DP(newsize); int mxn = 0;
	/*for (int i = 0; i < newsize; i++) {
		cout << SUBTRAIN[i] << " ";
	}
	cout << "\n";*/
	for (int i = 0; i < newsize; i++) { // 2개 고르는 경우 세팅
		if (i < nn) {
			DP[i] = 0;
		}
		else {
			if (mxn < SUBTRAIN[i - nn]) {
				mxn = SUBTRAIN[i- nn];
			}
			DP[i] = mxn + SUBTRAIN[i];
		}
	}
	mxn = 0;
	for (int i = 0; i < newsize; i++) { // 3개 고르는 경우 세팅
		if (i < nn) {
			DP[newsize - i - 1] = 0;
		}
		else {
			if (mxn < SUBTRAIN[newsize - i - 1 + nn]) {
				mxn = SUBTRAIN[newsize - i - 1 + nn];
			}
			DP[newsize - i - 1] = mxn + DP[newsize - i - 1];
		}
	}
	/*for (int i = 0; i < newsize; i++) {
		cout << DP[i] << " ";
	}*/
	cout << *max_element(DP.begin(), DP.end());
	//cout << passenger;
}