#include<iostream>
#include<algorithm>
using namespace std;
int ydir[] = { -1,0,1,0 };    // 상, 우, 하, 좌 방향벡터
int xdir[] = { 0,1,0,-1 };
string go;
char map[101][101];
int n;
int minY = 101;
int maxY = 0;
int minX = 101;
int maxX = 0;

void Check(int y, int x) {    // 맵 찍을 바운더리 체크
	minY = min(minY, y);
	maxY = max(maxY, y);
	maxX = max(maxX, x);
	minX = min(minX, x);
}

void Move() {    // 움직이겠음
	int dirIdx = 2;    // 남쪽부터
	int y = 50, x = 50;    // 중앙에서 시작
	for (int i = 0; i < go.size(); i++)
	{
		if (go[i] == 'L') {    // 왼쪽으로 꺾을거면
			dirIdx -= 1;       // 방향벡터 한 칸 전
			if (dirIdx < 0)dirIdx = 3;
		}
		else if (go[i] == 'R') {    // 오른쪽으로 꺾을거면
			dirIdx += 1;            // 방향벡터 한 칸 앞
			if (dirIdx > 3)dirIdx = 0;
		}
		else {
			map[y][x] = '.';    // 이동했다면 점 찍기
			Check(y, x);        // 바운더리 체크

			y += ydir[dirIdx];
			x += xdir[dirIdx];
			Check(y, x);
		}
	}
	map[y][x] = '.';
	Check(y, x);
}

int main() {
	cin >> n;

	cin >> go;

	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			map[i][j] = '_';	// '_'는 범위 밖 더미 값들
		}
	}
	Move();
	for (int i = minY; i <= maxY; i++)    // 바운더리 내에서만
	{
		for (int j = minX; j <= maxX; j++)
		{
			if (map[i][j] == '_')
				cout << "#";            // 벽 출력
			else
				cout << map[i][j];      // 이동한 거리 출력  
		}cout << "\n";
	}
}