/*
* invalid 조건
* 1. X >= O + 2
* 2. X == O + 1
*	2-1. 9개 채워져 있음 : O빙고
*	2-2. 덜 채워져 있음 : X빙고가 아닐 때
* 3. X == O : O빙고가 아닐 때
* 4. X < O
*
* 필요한 기능
* 1. X와 O개수 세기
* 2. 빙고 여부
*/

#include<iostream>
#include<string.h>
#include<string>
using namespace std;
int bingoIdx[][3] = {
	0,3,6,
	1,4,7,
	2,5,8,
	0,1,2,
	3,4,5,
	6,7,8,
	0,4,8,
	2,4,6,
};
// X와 O개수 세기
int CountCheck(string str, char ch) {
	int cnt = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ch)cnt++;
	}
	return cnt;
}

// 빙고 여부
bool BingoCheck(string str, char ch) {
	bool isBingo = false;
	for (int i = 0; i < 8; i++)
	{
		int cnt = 0;
		for (int j = 0; j < 3; j++)
		{
			if (str[bingoIdx[i][j]] == ch)
				cnt++;
		}
		if (cnt == 3) {
			isBingo = true;
			return isBingo;
		}
	}
	return isBingo;
}

// true : valid, false : invalid
bool ValidCheck(string str) {
	int cntX = CountCheck(str, 'X');
	int cntO = CountCheck(str, 'O');
	if (cntX >= cntO + 2 || cntX < cntO)return false;
	else if (cntX == cntO) {
		if (!BingoCheck(str, 'O'))return false;
		if (cntX + cntO != 9 && BingoCheck(str, 'X'))return false;
	}
	else if (cntX == cntO + 1) {
		if (cntX + cntO == 9) {
			if (BingoCheck(str, 'O'))
				return false;
		}
		else {
			if (!BingoCheck(str, 'X'))
				return false;
			else {
				if (BingoCheck(str, 'O'))
					return false;
			}
		}
	}
	return true;
}

void init() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
}
void input() {
	while (1) {
		string str;
		cin >> str;
		if (strcmp(str.c_str(), "end") == 0)break;
		else {
			if (ValidCheck(str))
				cout << "valid\n";
			else
				cout << "invalid\n";
		}
	}
}

int main() {
	init();
	input();
	return 0;
}