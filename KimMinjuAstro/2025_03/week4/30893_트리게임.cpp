#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int N, S, E;
vector<int>alis[100001];
int visitied[100001];
struct Node
{
	int num;
	int depth;
};
vector<int>route;
bool SecondIsWin = false;
void WhosGonnaWin() {
	for (int i = 0; i < route.size() - 1; i++)
	{
		if (i % 2 == 1) {
			for (int j = 0; j < alis[route[i]].size(); j++)
			{
				if (alis[route[i]][j] != route[i + 1] && alis[route[i]][j] != route[i-1]) {
					SecondIsWin = true;
					return;
				}
			}
		}
	}
}
void dfs(int now) {
	if (now == E) {
		WhosGonnaWin();
		return;
	}

	for (int i = 0; i < alis[now].size(); i++)
	{
		int next = alis[now][i];
		if (visitied[next] == 1)continue;
		visitied[next] = 1;
		route.push_back(next);
		dfs(alis[now][i]);
		route.pop_back();
		visitied[next] = 0;
	}

}
int main() {
	cin >> N >> S >> E;
	for (int i = 0; i < N - 1; i++)
	{
		int from, to;
		cin >> from >> to;
		alis[from].push_back(to);
		alis[to].push_back(from);
	}
	int de = -1;

	visitied[S] = 1;
	route.push_back(S);
	dfs(S);
	if (SecondIsWin)cout << "Second\n";
	else cout << "First\n";
}