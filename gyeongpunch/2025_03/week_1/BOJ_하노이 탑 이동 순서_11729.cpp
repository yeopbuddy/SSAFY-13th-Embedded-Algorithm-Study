#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

// 몇 번째 원판인지를 출력하지 않아도 되어서 비교적 쉽게 구할 수 있는 문제였습니다.
// N개의 원판을 from에서 to로 옮기기 위해서는 N-1개의 원판을 6-(from+to)로 옮겨놓고 맨 밑에 있는 1개의 원판을 to로 옮긴 후,
// 6-(from+to)에 있는 N-1개의 원판을 to로 옮깁니다.

struct Info{
    int from;
    int to;
};

int totalCnt = 0;
int N;
vector<Info> result;

void Hanoi(int depth, int from, int to){
    if(depth == 1){
        result.push_back({from, to});
        totalCnt++;
        return;
    }
    Hanoi(depth - 1, from, 6 - (from + to));
    Hanoi(1, from, to);
    Hanoi(depth-1, 6 - (from + to), to);
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N;

    Hanoi(N, 1, 3);

    cout << totalCnt << '\n';
    for(Info a : result){
        cout << a.from << ' ' << a.to << '\n';
    }

    return 0;
}