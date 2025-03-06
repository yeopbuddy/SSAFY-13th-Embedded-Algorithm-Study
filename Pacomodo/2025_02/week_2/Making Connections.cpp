// 25832번 Making Connections
// 유파
#include <iostream>
#include <vector>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
typedef long long ll;

ll gcd(ll a, ll b){
    ll temp, r;
    if (a < b){
        temp = a;
        a = b;
        b = temp;
    }
    while (b != 0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int find(vector<int>& P, int node){
    if (P[node] != node){
        P[node] = find(P, P[node]);
    }
    return P[node];
}

void merge(vector<int>& C, vector<int>& P, int node1, int node2, ll& U, ll& V){
    int P1 = find(P, node1), P2 = find(P, node2);
    if (P1 != P2){
        V--;// 그룹이 서로 다르다면 합치는 작업 진행. 총 그룹 수는 1개 줄어든다.
        U += 2*(ll)C[P1]*(ll)C[P2]; // 기존에 a^2 + b^2 + ...에서 (a+b)^2 + ...로 바뀜. 2*a*b만큼 늘어남
        if (P1 < P2){
            P[P2] = P1;
            C[P1] += C[P2];
        }
        else {
            P[P1] = P2;
            C[P2] += C[P1];
        }
    }
    return;
}

int main(void){
    fastio;
    int N, M; cin >> N >> M; // the number of computers, the number of query
    vector<int> P(N+1);
    vector<int> C(N+1);
    for (int i=0; i < N+1; i++){
        P[i] = i;
    }
    fill(C.begin(), C.end(), 1);
    int Q, u, v;
    ll U = N, V = N;
    ll G;
    while (M--){
        cin >> Q;
        if (Q == 1){
            cin >> u >> v;
            merge(C, P, u, v, U, V);
        }
        else{
            G = gcd(U, V);
            cout << U/G << '/' << V/G << endl;
        }
    }
    return 0;
}