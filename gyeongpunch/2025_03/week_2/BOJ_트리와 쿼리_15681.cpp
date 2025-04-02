#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// tree: 전체 트리를 나타내는 인접리스트
// children: i번째 노드의 자식을 담는다.
// parents: i번째 노드의 부모를 담는다.
// subTreeSize: i번째 노드를 루트로 하는 서브트리의 크기

// 완탐 한 번만 돌리면 위에를 모두 알 수 있습니다.

const int MAX_N = 100001;

int N, R, Q;
vector<int> tree[MAX_N];
vector<int> children[MAX_N];
int parents[MAX_N];
int subTreeSize[MAX_N];

void makeTree(int nowNode, int parent) {

	subTreeSize[nowNode] = 1;
	for (int neighbor : tree[nowNode]) {
		if (neighbor == parent) continue;

		children[nowNode].push_back(neighbor);
		parents[neighbor] = nowNode;
		makeTree(neighbor, nowNode);
		subTreeSize[nowNode] += subTreeSize[neighbor];
	}
}

int main(void) {
	fastio;

	cin >> N >> R >> Q;

	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	makeTree(R, -1);

	for (int i = 0; i < Q; i++) {
		cin >> a;
		cout << subTreeSize[a] << '\n';
	}


	return 0;
}