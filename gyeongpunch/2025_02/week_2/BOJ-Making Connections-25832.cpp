#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

// 인접리스트로 푸는데 루트 찾는 과정이 너무 오래걸려서 검색을 해보니 유니온 파인드라는 게 있더군요.
// cmd가 1이면 u와 v의 루트를 찾아서 한 쪽으로 붙여주고, 이미 계산했던 curr_sm과 curr_cnt를 업데이트 해줍니다.
// 노드 개수가 100000개이고 제곱을 하니까 int형은 타입 오버플로우가 발생하므로 long long으로 처리해줍니다.

const int MAX_NODE = 100001;
int N, M;
int parent[MAX_NODE], sz[MAX_NODE];
long long curr_sm;
int curr_cnt;

int find(int u) {
	if (parent[u] == u) return u;

	parent[u] = find(parent[u]);
	return parent[u];
}

void unite(int u, int v) {
	int rootU = find(u);
	int rootV = find(v);
	if (rootU == rootV) return;

	curr_sm -= (1LL * sz[rootU] * sz[rootU]);
	curr_sm -= (1LL * sz[rootV] * sz[rootV]);

	parent[rootV] = rootU;
	sz[rootU] += sz[rootV];

	curr_sm += (1LL * sz[rootU] * sz[rootU]);

	curr_cnt--;
}

int gcd(long long a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

int main() {
	fastio;

	int N, M, cmd, u, v;
	long long g;
	cin >> N >> M;

	curr_sm = N;
	curr_cnt = N;

	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		sz[i] = 1;
	}

	for(int i = 0; i < M; i++) {
		cin >> cmd;

		if (cmd == 1) {
			cin >> u >> v;
			unite(u, v);
		}
		else if (cmd == 2) {
			g = gcd(curr_sm, curr_cnt);
			cout << curr_sm / g << "/" << curr_cnt / g << '\n';
		}
	}

	return 0;
}
