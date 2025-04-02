#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(nullptr);

using namespace std;

#define MAX_N 50

/*
오래 걸리는 기준이 서브 트리 크기인가 height인가 하다가 그때그때마다 동적으로 구해야하는 반례를 찾아서 그때그때 구해봅시다.

listen[i] : i번째 노드를 루트로 하는 서브 트리에서 모든 직원이 소식을 듣는 데 걸리는 시간의 최솟값

v 벡터에는 현재 노드인 now의 직속 부하의 listen값을 담습니다.
1. 부하가 없는 직원은 직속 부하가 없으므로 v에는 아무런 값이 안 담기고 tree[leaf]에도 아무런 값이 없으므로 listen[leaf] = 0 이 됩니다.
2. 부하가 있는 직원은 v벡터를 내림차순으로 정렬합니다. 왜냐하면 오래걸리는 부하부터 전달해줘야 시간이 더 적게 걸리기 때문입니다.
    그러고 tree[now].size() 만큼 루프를 도는데 v[i] + i + 1의 최댓값으로 listen[now]에 저장합니다.
    인덱스가 0부터 시작하기 때문에 +1 해줬습니다.

루프를 다 돌면 현재 노드의 시간 최솟값이 listen에 저장되어있습니다.
이제 위로 쭉쭉 타고 올라가면서 반복하면 됩니다.
*/

vector<int> tree[MAX_N];
int listen[MAX_N];
int N;

void get_listen(int now){
    vector<int> v;

    for(int child : tree[now]){
        get_listen(child);
        v.push_back(listen[child]);
    }
    
    sort(v.begin(), v.end(), greater<int>());

    for(int i=0; i<tree[now].size(); i++){
        listen[now] = max(listen[now], v[i] + i + 1);
    }
}

int main(void){
    fastio;
    
    // freopen("input.txt", "r", stdin);

    cin >> N;

    int a;
    for(int i=0; i<N; i++){
        cin >> a;
        
        if(i == 0) continue;

        tree[a].push_back(i);
    }

    get_listen(0);

    cout << listen[0] << '\n';

    return 0;
}