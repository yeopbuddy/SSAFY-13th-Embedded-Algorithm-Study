#include<iostream>
#include<vector>
using namespace std;
int n, m;	// n : 만들어야 할 수, m : 개수
int map[3][3];
int ydir[] = { -1,0,1,0 };
int xdir[] = { 0,1,0,-1 };
int visited[3][3];
bool flag = false;
struct Node
{
	int num;
	int y;
	int x;
};
vector<Node>v;
void dfs(int now, int y, int x) {
	if (flag)return;
	if (now == m * 2 - 1) {
		//for (int i = 0; i < v.size(); i++)
		//{
		//	cout << v[i].num << " ";
		//}
		int total=v[0].num;
		for (int i = 1; i < v.size(); i += 2)
		{
			if (v[i].num == 10)
				total += v[i + 1].num;
			else if (v[i].num == 11)
				total -= v[i + 1].num;
		}
		//cout << "\n";
		//cout << " : "<<total;
		if (total == n) {
			cout << 1 << "\n";
			for (int i = 0; i < v.size(); i++)
			{
				cout << v[i].y << " " << v[i].x << "\n";
			}
			flag = true;
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || ny >= 3 || nx < 0 || nx >= 3)continue;
		if (visited[ny][nx] == 1)continue;
		visited[ny][nx] = 1;
		v.push_back({ map[ny][nx], ny, nx });
		dfs(now + 1, ny, nx);
		visited[ny][nx] = 0;
		v.pop_back();
	}
	

}
int main() {
	cin >> n >> m;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			char ch;
			cin >> ch;
			if (ch >= '0' && ch <= '9')
				map[i][j] = ch - '0';
			else if (ch == '+')
				map[i][j] = 10;	// 플러스는 10
			else if (ch == '-')
				map[i][j] = 11;	// 마이너스는 11
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (flag)break;
			if ((i + j) % 2 == 1)continue;
			memset(visited, 0, sizeof(visited));
			visited[i][j] = 1;

			v.clear();
			v.push_back({ map[i][j], i, j });
			dfs(1, i, j);
		}
	}
	if(!flag)
		cout << 0 << "\n";
}