// 5639번 이진 검색 트리
// 트리, 재귀, 이분 탐색
/*
접근 방법:
분할 정복으로 트리를 재 구성 하자.
전위 순회는 루트 - 왼쪽 - 오른쪽 순이다.
즉, 임의의 전위 순회 결과 리스트가 주어지면, 다음과 같이 재귀적으로 분리할 수 있다.
[루트] [루트보다 작은 애들] [루트보다 큰 애들]
루트보다 작은 애들은 루트 왼쪽에 있는 애들이고,
루트보다 큰 애들은 루트 오른쪽에 있는 애들이다.
후위 순회는 왼쪽 - 오른쪽 - 루트 순이다.
[루트] [루트보다 작은 애들] [루트보다 큰 애들]
로 이전에 분리해놓았으므로,
[루트보다 작은 애들] [루트보다 큰 애들] [루트] 순으로 출력하도록 한다.
물론, [루트보다 작은 애들]과 [루트보다 큰 애들] 또한 하나의 리스트이므로,
각각의 리스트에 대해서 재귀 적용을 해준다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

void recur(const vector<int>& list, int start_idx, int end_idx){
    if (start_idx > end_idx){
        return;
    }
    if (start_idx == end_idx){
        cout << list[end_idx] << endl;
        return;
    }
    int root = list[start_idx];
    auto it = lower_bound(list.begin()+start_idx+1, list.begin()+end_idx+1, root);
    int right_idx = distance(list.begin(), it);
    recur(list, start_idx+1, right_idx-1);
    recur(list, right_idx, end_idx);
    cout << root << endl;
    return;
}

int main(void){
    fastio;
    vector<int> list;
    int node;
    while (cin >> node){
        list.push_back(node);
    }
    recur(list, 0, list.size()-1);
    return 0;
}