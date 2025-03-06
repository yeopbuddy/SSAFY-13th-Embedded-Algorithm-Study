#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <queue>

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

using namespace std;

// 완전탐색 했다가 또 시간초과로 떠서 고민하다가 dp 테이블 정의만 구글링했습니다.ㅎ
// dp[i][j][k]: SCV의 체력이 각각 i, j, k일 때까지의 최소 공격 횟수
// N==1이라면 9로 계속 빼면 되니까 수학으로 바로 답을 구할 수 있습니다.

// N==2이면 greedy하게 체력이 많이 남은 쪽에서 9을 빼고, 나머지는 3을 빼다가 
// 어느 하나가 0이하로 내려가면 get_one_scv로 답을 구할 수 있습니다.

// N==3일 때는 중복 계산을 하지않게 BFS로 진행하면서 DP 테이블을 업데이트합니다.
// BFS로 진행하므로 각 체력까지의 최소 횟수를 구할 수 있습니다.

const int MAX_HP = 60;

struct SCV {
	int hp1, hp2, hp3;
};

int dp[MAX_HP + 1][MAX_HP + 1][MAX_HP + 1];
vector<vector<int>> damage_permu;
int visited[3] = { 0 };
vector<int> tmp;
int damage[3] = { 9, 3, 1 };
int permu_length;

void dfs(int depth) {
	if (depth == 3) {
		damage_permu.push_back(tmp);
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (visited[i] == 0) {
			visited[i] = 1;
			tmp.push_back(damage[i]);
			dfs(depth + 1);
			tmp.pop_back();
			visited[i] = 0;
		}
	}
}

int get_one_scv(int hp) {
	return (hp + 8) / 9;
}

int get_two_scv(int hp1, int hp2) {
	int cnt = 0;

	while (hp1 > 0 || hp2 > 0) {
		if (hp1 > hp2) {
			hp1 -= 9;
			hp2 -= 3;
		}
		else {
			hp1 -= 3;
			hp2 -= 9;
		}
		cnt++;

		if (hp1 == 0 || hp2 == 0) {
			cnt += get_one_scv(hp1 + hp2);
			break;
		}
	}
	return cnt;
}

int bfs(SCV scv) {
	queue<SCV> q;
	q.push(scv);
	dp[scv.hp1][scv.hp2][scv.hp3] = 0;

	sort(damage, damage + 3);


	SCV cur;
	int nxt_hp1, nxt_hp2, nxt_hp3;

	while (!q.empty()) {
		cur = q.front(); q.pop();

		if (cur.hp1 == 0 && cur.hp2 == 0 & cur.hp3 == 0) {
			return dp[0][0][0];
		}

		for (int i = 0; i < permu_length; i++) {
			nxt_hp1 = max(0, cur.hp1 - damage_permu[i][0]);
			nxt_hp2 = max(0, cur.hp2 - damage_permu[i][1]);
			nxt_hp3 = max(0, cur.hp3 - damage_permu[i][2]);

			if (dp[nxt_hp1][nxt_hp2][nxt_hp3] == -1) {
				q.push({ nxt_hp1, nxt_hp2, nxt_hp3 });
				dp[nxt_hp1][nxt_hp2][nxt_hp3] = dp[cur.hp1][cur.hp2][cur.hp3] + 1;
			}
		}
	}
	return -1;
}

int main(void) {
	fastio;

	int N, hp1, hp2, hp3, result;
	cin >> N;
	if (N == 1) {
		cin >> hp1;
		result = get_one_scv(hp1);
	}
	else if (N == 2) {
		cin >> hp1 >> hp2;
		result = get_two_scv(hp1, hp2);
	}
	else if (N == 3) {
		dfs(0);
		permu_length = damage_permu.size();
		SCV scv;
		cin >> scv.hp1 >> scv.hp2 >> scv.hp3;
		memset(dp, -1, sizeof(dp));
		result = bfs(scv);
	}

	cout << result << '\n';

	return 0;
}