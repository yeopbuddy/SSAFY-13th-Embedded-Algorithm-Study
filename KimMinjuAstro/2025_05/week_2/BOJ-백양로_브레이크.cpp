#include<iostream>
using namespace std;
int n, m;
int k;
int road[251][251];
void FloydWarshall() {
	for (int mid = 1; mid <= n; mid++)
	{
		for (int start = 1; start <= n; start++)
		{
			for (int end = 1; end <= n; end++)
			{
				if (road[start][end] > road[start][mid] + road[mid][end])
					road[start][end] = road[start][mid] + road[mid][end];
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			road[i][j] = 10e8;
		}
	}

	for (int i = 0; i < m; i++)
	{
		int u, v, b;
		cin >> u >> v >> b;

		road[u][u] = 0;
		road[v][v] = 0;
		road[u][v] = 0;

		if (b == 0)
			road[v][u] = 1;
		else
			road[v][u] = 0;
	}


	FloydWarshall();

	cin >> k;
	for (int i = 0; i < k; i++)
	{
		int s, e;
		cin >> s >> e;
		cout << road[s][e] << "\n";
	}
}