#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int N, L;
int map[101][101];
int ramp[101][101];
int cnt = 0;
void rowCheck(int line) {
	bool failFlag = false;

	for (int i = 0; i < N-1; i++)
	{
		int now = map[line][i];
		int next = map[line][i + 1];
		
		// 다른 경사로 발견
		if (now != next) {

			// 경사로가 2이상 차이 나면 불가
			if (abs(now - next) >= 2)failFlag = true;

			// 한 칸 올라감
			else if (now - next == -1) {
				bool onRamp = true;

				if(ramp[line][i]==1)failFlag = true;
				// 전의 높이 다 확인
				for (int j = 1; j < L; j++)
				{
					// 경사로 만큼의 길이가 있는지부터 확인
					if (i - j < 0) { failFlag = true; break; }

					// 이미 경사로를 놓은 곳이면 불가
					if (ramp[line][i - j] == 1) { failFlag = true; break; }
					else {
						// 경사로 길이만큼의 개수가 now 높이와 같지 않으면 불가
						if (map[line][i - j] != now) { failFlag = true; 
						onRamp = false;
						break; }
					}
				}
				// 전의 높이를 다 확인했는데 경사로를 놓을 수 있다면
				if (!failFlag&&onRamp) {
					for (int j = 0; j < L; j++)
					{
						// 경사로 놓은 것으로 취급
						ramp[line][i - j] = 1;
					}
				}
			}

			// 한 칸 내려감
			else if (now - next == 1) {
				bool onRamp = true;
				for (int j = 1; j <= L; j++)
				{

					if (i + j >= N) { failFlag = true; break; }

					if (ramp[line][i + j] == 1) { failFlag = true; break; }
					else {
						if (map[line][i + j] != next) { failFlag = true; 
						onRamp = false;
						}
					}
				}
				if (!failFlag&&onRamp) {
					for (int j = 1; j <= L; j++)
					{
						ramp[line][i + j] = 1;
					}
				}
			}
		}
	}

	// 그 많은 역경을 뚫고도 플래그를 안 세웠다면 추가
	if (!failFlag) {
		//cout << "rowCheck " << line << " 가능" << "\n";
		cnt++;
	}
}

void colCheck(int line) {
	bool failFlag = false;
	for (int i = 0; i < N - 1; i++)
	{
		int now = map[i][line];
		int next = map[i + 1][line];

		// 다른 경사로 발견
		if (now != next) {

			// 경사로가 2이상 차이 나면 불가
			if (abs(now - next) >= 2)failFlag = true;

			// 한 칸 올라감
			else if (now - next == -1) {
				if (ramp[i][line] == 1)failFlag = true;

				bool onRamp = true;
				// 전의 높이 다 확인
				for (int j = 1; j < L; j++)
				{
					// 경사로 만큼의 길이가 있는지부터 확인
					if (i - j < 0) { failFlag = true; break; }

					// 이미 경사로를 놓은 곳이면 불가
					if (ramp[i - j][line] == 1) { failFlag = true; break; }
					else {
						// 경사로 길이만큼의 개수가 now 높이와 같지 않으면 불가
						if (map[i - j][line] != now) { failFlag = true; 
						onRamp = false;
						break; }
					}
				}
				// 전의 높이를 다 확인했는데 경사로를 놓을 수 있다면
				if (!failFlag&&onRamp) {
					for (int j = 0; j < L; j++)
					{
						// 경사로 놓은 것으로 취급
						ramp[i - j][line] = 1;
					}
				}
			}

			// 한 칸 내려감
			else if (now - next == 1) {
				bool onRamp = true;
				for (int j = 1; j <= L; j++)
				{

					if (i + j >= N) { failFlag = true; break; }

					if (ramp[i + j][line] == 1) { failFlag = true; break; }
					else {
						if (map[i + j][line] != next) { failFlag = true;onRamp = false; }
					}
				}
				if (!failFlag&&onRamp) {
					for (int j = 1; j <= L; j++)
					{
						ramp[i + j][line] = 1;
					}
				}
			}
		}
	}

	// 그 많은 역경을 뚫고도 플래그를 안 세웠다면 추가
	if (!failFlag) {
		//cout << "colCheck " << line << " 가능" << "\n";
		cnt++;
	}
}
int main() {
	cin >> N >> L;	// L : 경사로의 길이
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		rowCheck(i);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// 경사로 체크 배열 초기화
			ramp[i][j] = 0;
		}
	}


	for (int j = 0; j < N; j++)
	{
		colCheck(j);
	}
	cout << cnt << "\n";


}
