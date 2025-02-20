#include <iostream>
using namespace std;

void Score(int ru[], int g1, int g2, int g3, int g4, int g5, int g6) {
	if (g1 == 0)
		ru[0] += 3;
	else if (g1 == 1)
		ru[1] += 3;
	else {
		ru[0]++;
		ru[1]++;
	}
	if (g2 == 0)
		ru[0] += 3;
	else if (g2 == 1)
		ru[2] += 3;
	else {
		ru[0]++;
		ru[2]++;
	}
	if (g3 == 0)
		ru[0] += 3;
	else if (g3 == 1)
		ru[3] += 3;
	else {
		ru[0]++;
		ru[3]++;
	}
	if (g4 == 0)
		ru[1] += 3;
	else if (g4 == 1)
		ru[2] += 3;
	else {
		ru[1]++;
		ru[2]++;
	}
	if (g5 == 0)
		ru[1] += 3;
	else if (g5 == 1)
		ru[3] += 3;
	else {
		ru[1]++;
		ru[3]++;
	}
	if (g6 == 0)
		ru[2] += 3;
	else if (g6 == 1)
		ru[3] += 3;
	else {
		ru[2]++;
		ru[3]++;
	}
}

int check(int ru[]) {
	//ru[0]이 1등일 때
	if (ru[0] >= ru[1] && ru[0] >= ru[2] && ru[0] >= ru[3])
		return 1;

	//ru[0]이 2등일 때
	//ru[1]이 1등
	if (ru[1] > ru[0] && ru[1] >= ru[2] && ru[1] >= ru[3]) {
		if (ru[0] >= ru[2] && ru[0] >= ru[3])
			return 1;
		else
			return 0;
	}
	//ru[2]이 1등
	else if (ru[2] > ru[0] && ru[2] > ru[1] && ru[2] >= ru[3]) {
		if (ru[0] >= ru[1] && ru[0] >= ru[3])
			return 1;
		else 
			return 0;
	}
	//ru[3]이 1등
	else if (ru[3] > ru[0] && ru[3] > ru[1] && ru[3] > ru[2]) {
		if (ru[0] >= ru[1] && ru[0] >= ru[2])
			return 1;
		else
			return 0;
	}

	return 0;
}

double Cal(int per[], int g1, int g2, int g3, int g4, int g5, int g6) {
	double tmp[6];

	if (g1 == 0)
		tmp[0] = double(4 * per[0]) / (5 * per[0] + 5 * per[1]);
	else if (g1 == 1)
		tmp[0] = double(4 * per[1]) / (5 * per[0] + 5 * per[1]);
	else
		tmp[0] = double(per[0] + per[1]) / (5 * per[0] + 5 * per[1]);

	if (g2 == 0)
		tmp[1] = double(4 * per[0]) / (5 * per[0] + 5 * per[2]);
	else if (g2 == 1)
		tmp[1] = double(4 * per[2]) / (5 * per[0] + 5 * per[2]);
	else
		tmp[1] = double(per[0] + per[2]) / (5 * per[0] + 5 * per[2]);

	if (g3 == 0)
		tmp[2] = double(4 * per[0]) / (5 * per[0] + 5 * per[3]);
	else if (g3 == 1)
		tmp[2] = double(4 * per[3]) / (5 * per[0] + 5 * per[3]);
	else
		tmp[2] = double(per[0] + per[3]) / (5 * per[0] + 5 * per[3]);

	if (g4 == 0)
		tmp[3] = double(4 * per[1]) / (5 * per[1] + 5 * per[2]);
	else if (g4 == 1)
		tmp[3] = double(4 * per[2]) / (5 * per[1] + 5 * per[2]);
	else
		tmp[3] = double(per[1] + per[2]) / (5 * per[1] + 5 * per[2]);

	if (g5 == 0)
		tmp[4] = double(4 * per[1]) / (5 * per[1] + 5 * per[3]);
	else if (g5 == 1)
		tmp[4] = double(4 * per[3]) / (5 * per[1] + 5 * per[3]);
	else
		tmp[4] = double(per[1] + per[3]) / (5 * per[1] + 5 * per[3]);

	if (g6 == 0)
		tmp[5] = double(4 * per[2]) / (5 * per[2] + 5 * per[3]);
	else if (g6 == 1)
		tmp[5] = double(4 * per[3]) / (5 * per[2] + 5 * per[3]);
	else
		tmp[5] = double(per[2] + per[3]) / (5 * per[2] + 5 * per[3]);

	return tmp[0] * tmp[1] * tmp[2] * tmp[3] * tmp[4] * tmp[5] * 100;
}

int main() {
	int per[4];
	for (int i = 0; i < 4; i++)
		cin >> per[i];

	double ans = 0;
	for (int g1 = 0; g1 < 3; g1++)
		for (int g2 = 0; g2 < 3; g2++)
			for (int g3 = 0; g3 < 3; g3++)
				for (int g4 = 0; g4 < 3; g4++)
					for (int g5 = 0; g5 < 3; g5++)
						for (int g6 = 0; g6 < 3; g6++) {
							int ru[4] = { 0 };

							//각 결과마다 루돌프 점수 계산
							Score(ru, g1, g2, g3, g4, g5, g6);
							
							//ru[0]이 2등 안에 드는지 체크
							if (check(ru))
								ans += Cal(per, g1, g2, g3, g4, g5, g6);
						}
	cout << fixed;
	cout.precision(3);
	cout << ans;
}