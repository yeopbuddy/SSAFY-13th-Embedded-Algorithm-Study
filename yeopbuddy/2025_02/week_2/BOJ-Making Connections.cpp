#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int group[100001];
long long under, over;
map<int, int> num2groupz;
map<int, int> underandover;

int find(int node){
    if(node == group[node]) return node;
    return group[node] = find(group[node]);
}

void Union(int a, int b){
    int rootA = find(a);
    int rootB = find(b);
    if(rootA != rootB){
        // 기존 크기 가져오기
        int szA = num2groupz[rootA];
        int szB = num2groupz[rootB];

        // 기존 크기 갱신 (해당 크기 그룹 개수 줄이기)
        underandover[szA]--;
        if (underandover[szA] == 0) underandover.erase(szA);
        
        underandover[szB]--;
        if (underandover[szB] == 0) underandover.erase(szB);

        // 합치는 과정 (루트 설정)
        group[rootB] = rootA;
        num2groupz[rootA] += szB;  // rootA에만 크기 증가 반영
        num2groupz.erase(rootB);   // rootB는 이제 필요 없음
        
        // 새로운 크기 추가
        underandover[num2groupz[rootA]]++;
    }
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    int oneortwo, nod1, nod2;
    underandover[1] = n;

    // 초기화
    for(int i = 1; i <= n; i++){
        group[i] = i;
        num2groupz[i] = 1;
    }

    for(int i = 0; i < q; i++){
        cin >> oneortwo;
        if(oneortwo == 2){
            under = 0;
            over = 0;
            for(auto j = underandover.begin(); j != underandover.end(); j++){
                under += j->second;
                over += (long long)j->first * j->first * j->second;
            }
            long long gcd = __gcd(over, under);
            cout << over/gcd << "/" << under/gcd << "\n";
        }
        else{
            cin >> nod1 >> nod2;
            Union(nod1, nod2);
        }
    }
}