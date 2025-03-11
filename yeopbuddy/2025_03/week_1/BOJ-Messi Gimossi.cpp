#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
	string MSMSG = "Messi Messi Gimossi";
	string MSG = "Messi Gimossi ";
	int n; cin >> n;
	if (n <= 14) { // 작은 값 처리
		if (n == 6 || n == 14) {
			cout << MSMSG;
		}
		else {
			cout << MSG[n - 1];
		}
	}
	else {
		long long sl1 = 6; long long sl2 = 14; long long sl3 = sl1 + sl2;
		long long leninfo[50] = { 0 };
		leninfo[0] = sl1; leninfo[1] = sl2; leninfo[2] = sl3;
		int m = 3;
		while (n > sl3) { // 길이 배열 생성
			sl1 = sl2; sl2 = sl3; sl3 = sl1 + sl2;
			leninfo[m] = sl3;
			m++;
		}
		m--;
		while (n > 14) {
			if (n >= leninfo[m]) {
				n -= leninfo[m];
			}
			else {
				m--;
			}
		}
		if (n == 6 || n == 14 || n == 0) {
			cout << MSMSG;
		}
		else {
			cout << MSG[n - 1];
		}
	}
}