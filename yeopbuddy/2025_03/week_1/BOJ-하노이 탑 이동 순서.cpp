#include <iostream>
using namespace std;

// 구현할 때마다 헷갈리는 하노이의 탑 문제
// 3개의 탑을 각각 st(start), md(middle), ed(end)로 정한다.
// st에서 md를 거쳐 ed로 모두 보내는 것이 목표
// 하나가 남았을 경우(가장 작은 원판을 제외하고 모두 ed에 쌓였을 경우) st에서 ed로 보내고 리턴//
// 아닐 경우, st에서 ed를 거쳐 md로 먼저 보낸다.
// 그 후, md에서 st를 거쳐 ed로 보낸다.

void hanoi(int n, int st, int md, int ed){
    if(n == 1){ // if one left, move final one and return
        cout << st << " " << ed << "\n";
        return;
    }
    hanoi(n-1, st, ed, md); // move st -> md
    cout << st << " " << ed << "\n";
    hanoi(n-1, md, st, ed); // move md -> ed
}

int main(){
    int k; cin >> k;
    cout << (1 << k) - 1 << "\n";
    hanoi(k, 1, 2, 3);
    return 0;
}