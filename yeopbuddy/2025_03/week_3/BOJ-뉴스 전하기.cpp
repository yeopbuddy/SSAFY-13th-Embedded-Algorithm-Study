#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> COMPANY;

int DPDFS(int node) {
    vector<int> times;
    for(size_t i = 0; i < COMPANY[node].size(); i++){
        times.push_back(DPDFS(COMPANY[node][i])); // 재귀를 통해 구한 time 넣기
    }

    sort(times.begin(), times.end(), greater<>()); // time vector 내림차순 정렬

    int max_time = 0;
    for (int i = 0; i < times.size(); i++) {
        max_time = max(max_time, times[i] + i + 1); // 하위 노드 중 규칙에 맞는 가장 큰 값 찾기
    }

    return max_time; // ㅆ@방
}

int main() {
    int n, node;
    cin >> n >> node;
    COMPANY.resize(n);
    
    for (int i = 1; i < n; i++) {
        cin >> node;
        COMPANY[node].push_back(i);
    }

    cout << DPDFS(0);
}
