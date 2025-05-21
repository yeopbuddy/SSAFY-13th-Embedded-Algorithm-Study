#include <algorithm>
#include <iostream>
#include <vector>

#include <deque>
#include <string>

#define BOARD_SIZE 8

using namespace std;

int dy[] = {-1,-1, 0, 1, 1, 1, 0,-1, 0};
int dx[] = { 0, 1, 1, 1, 0,-1,-1,-1, 0};

int dy_wall = 1;
int dx_wall = 0;

struct Coord{
	int y, x;
};

class MovingMaze{
public:
	void InputTestCase(){
		for(int r = 0;r<BOARD_SIZE;r++)
			for(int c = 0;c<BOARD_SIZE;c++)
				{
					char in;
					cin>>in;
					if(in == '#')
						wall_pos_que.push_back({r,c});
				}
		player_pos_que.push_back({BOARD_SIZE - 1, 0});
	}

	int GetGameResult(){
		while(!player_pos_que.empty() && !wall_pos_que.empty())
			NextSec();
		if(player_pos_que.empty())
			return 0;
		else
			return 1;
	}

private:
	deque<Coord> player_pos_que;
	deque<Coord> wall_pos_que;

	bool CheckBound(Coord c){
		return -1 < c.y && c.y < BOARD_SIZE && -1 < c.x && c.x < BOARD_SIZE;
	}

	void NextSec(){
		vector<vector<int>> visited(BOARD_SIZE, vector<int>(BOARD_SIZE,false));

		for(Coord wall:wall_pos_que)
			visited[wall.y][wall.x] = true;
		
		int ppq_size = player_pos_que.size();
		for(int loop = 0;loop<ppq_size;loop++){
			Coord cur_pos = player_pos_que.front();
			player_pos_que.pop_front();
			if(visited[cur_pos.y][cur_pos.x])
				continue;
			player_pos_que.push_back(cur_pos);
		}
			

		ppq_size = player_pos_que.size();
		for(int loop = 0;loop<ppq_size;loop++){
			Coord cur_pos = player_pos_que.front();
			player_pos_que.pop_front();

			for(int dir = 0;dir<9;dir++){
				Coord next_pos;
				next_pos.y = cur_pos.y+dy[dir];
				next_pos.x = cur_pos.x+dx[dir];
				if(CheckBound(next_pos) && !visited[next_pos.y][next_pos.x]){
					visited[next_pos.y][next_pos.x]=true;
					player_pos_que.push_back(next_pos);
				}
			}
		}

		// for(auto& row: visited){
		// 	for(auto& ele: row)
		// 		cout<<ele;
		// 	cout<<endl;
		// }
		// cout<<endl;

		int wpq_size = wall_pos_que.size();
		for(int loop = 0;loop<wpq_size;loop++){
			Coord cur_pos = wall_pos_que.front();
			wall_pos_que.pop_front();
			Coord next_pos;
			next_pos.y = cur_pos.y + dy_wall;
			next_pos.x = cur_pos.x + dx_wall;
			if(CheckBound(next_pos))
				wall_pos_que.push_back(next_pos);
		}
	}
};

int main() {
	MovingMaze mm;
	mm.InputTestCase();
	cout<<mm.GetGameResult()<<endl;

	return 0;
}