#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<algorithm>
#include<queue>

using namespace std;

int n;
int x = 0, y = 0;
int d = 0;
// 0: ³² 1: ¼­ 2: ºÏ 3: µ¿
int minx = 0, miny = 0, maxx = 0, maxy = 0;

int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, -1, 0, 1 };

int main() {

	cin >> n;

	string cmd;
	cin >> cmd;

	for (int i = 0;i < cmd.length();i++) {
		if (cmd[i] == 'R') {
			d = (d + 1) % 4;
		}
		if (cmd[i] == 'L') {
			d = (d + 3) % 4;
		}
		if (cmd[i] == 'F') {
			y += dy[d];
			x += dx[d];

			//cout << y << "," << x << '\n';

			miny = min(miny, y);
			minx = min(minx, x);
			maxy = max(maxy, y);
			maxx = max(maxx, x);
		}

	}

	int r = maxy - miny + 1;
	int c = maxx - minx + 1;

	vector<vector<char>>miro(r, vector<char>(c, '#'));

	// ½ÃÀÛ yÁÂÇ¥: 0 - miny 
	// ½ÃÀÛ xÁÂÇ¥: 0 - minx


	int starty = -miny;
	int startx = -minx;

	miro[starty][startx] = '.';


	d = 0;
	for (int i = 0;i < cmd.length();i++) {
		if (cmd[i] == 'R') {
			d = (d + 1) % 4;
		}
		if (cmd[i] == 'L') {
			d = (d + 3) % 4;
		}
		if (cmd[i] == 'F') {
			starty += dy[d];
			startx += dx[d];
			miro[starty][startx] = '.';

		}
	}

	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			cout << miro[i][j];
		}
		cout << '\n';
	}


}