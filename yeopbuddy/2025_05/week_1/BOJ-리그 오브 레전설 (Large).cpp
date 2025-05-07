#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    int n = A.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return result;
}

vector<vector<long long>> power(vector<vector<long long>> base, long long exp) {
    int n = base.size();
    vector<vector<long long>> result(n, vector<long long>(n));
    for(int i = 0; i < n; ++i) result[i][i] = 1;

    while(exp > 0){
        if(exp % 2) result = multiply(result, base);
        base = multiply(base, base);
        exp /= 2;
    }
    return result;
}

long long k_fibonacci(long long x, long m) {
    if(x == 1 || x == m - 1) return 1;
    if(x == m) return 2;
    if(x < m) return 1;

    vector<vector<long long>> A(m, vector<long long>(m, 0));
    A[0][0] = 1;
    A[0][m - 1] = 1;
    for(int i = 1; i < m; ++i){
        A[i][i - 1] = 1;
    }

    vector<long long> initial(m, 1);
    initial[0] = 2;

    vector<vector<long long>> A_pow = power(A, x - m);

    long long result = 0;
    for(int i = 0; i < m; ++i){
        result = (result + A_pow[0][i] * initial[i]) % MOD;
    }
    return result;
}

int main() {
    long long x, m;
    cin >> x >> m;
    cout << k_fibonacci(x, m) << "\n";
    return 0;
}
