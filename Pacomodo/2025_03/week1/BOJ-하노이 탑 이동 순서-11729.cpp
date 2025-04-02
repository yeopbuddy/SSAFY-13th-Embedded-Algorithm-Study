// 11729번 하노이 탑 이동 순서
// 재귀
#include <iostream>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

void move(int N, int start, int end){
    int mid = 6-start-end;
    if (N == 1){
        cout << start << ' ' << end << endl;
        return;
    }
    move(N-1, start, mid);
    cout << start << ' ' << end << endl;
    move(N-1, mid, end);
    return;
}

int main(void){
    fastio;
    int N; cin >> N;
    cout << (1 << N) - 1 << endl;
    move(N, 1, 3);
    return 0;
}