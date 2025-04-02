#include <iostream>
#include <string>
using namespace std;
int main() {
	while (true) {
		string s; cin >> s;
		if (s == "end") {
			break;
		}
		else {
			int OCNT = 0; int XCNT = 0;
			for (int i = 0; i < 9; i++) {
				if (s[i] == 'O') {
					OCNT++;
				}
				else if (s[i] == 'X') {
					XCNT++;
				}
			}
			bool OWIN = false; bool XWIN = false;
			// 승리조건판단
			for (int i = 0; i < 3; i++) {
				if (s[i] == s[3 + i] && s[3 + i] == s[6 + i]) { // 가로 검사
					if (s[i] == 'O') {
						OWIN = true;
					}
					else if (s[i] == 'X') {
						XWIN = true;
					}
				}
				if (s[3 * i] == s[3 * i + 1] && s[3 * i + 1] == s[3 * i + 2]) {
					if (s[3 * i] == 'O') {
						OWIN = true;
					}
					else if (s[3 * i] == 'X') {
						XWIN = true;
					}
				}
			}
			if (s[0] == s[4] && s[4] == s[8]) {				
				if (s[4] == 'O') {
					OWIN = true;
				}
				else if (s[4] == 'X') {
					XWIN = true;
				}
			}
			if (s[2] == s[4] && s[4] == s[6]) {
				if (s[4] == 'O') {
					OWIN = true;
				}
				else if (s[4] == 'X') {
					XWIN = true;
				}
			}
			// valid, invalid 판단
			bool valid;
			if (OCNT + XCNT == 9) { // 칸 다 채워진 경우
				if (OWIN || XWIN) { // 누군가 이긴 경우
					if (OWIN && XWIN) { // 둘 다 이긴 경우
						valid = false;
					}
					else if (OWIN) { // O WIN
						valid = false;
					}
					else { // X WIN
						if (OCNT == 4 && XCNT == 5) {
							valid = true;
						}
						else {
							valid = false;
						}
					}
				}
				else { // 아무도 못 이긴 경우
					if (abs(OCNT - XCNT) >= 2 || OCNT > XCNT) {
						valid = false;
					}
					else {
						valid = true;
					}
				}
			}
			else { // 칸 다 안 채워진 경우
				if (OWIN || XWIN) { // 누군가 이긴 경우
					if (OWIN && XWIN) { // 둘 다 이긴 경우
						valid = false;
					}
					else if (OWIN) { // O WIN
						if (OCNT == XCNT) {
							valid = true;
						}
						else {
							valid = false;
						}
					}
					else { // X WIN
						if (OCNT+ 1 == XCNT) {
							valid = true;
						}
						else {
							valid = false;
						}
					}
				}
				else { // 아무도 못 이긴 경우	
					valid = false;
				}
			}
			if (valid) {
				cout << "valid\n";
			}
			else {
				cout << "invalid\n";
			}
		}
	}
}
