#include <iostream>
using namespace std;

const unsigned long long MOD = 1000000007;

unsigned long long power(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    unsigned long long k, p, n;
    cin >> k >> p >> n;
    unsigned long long multiplier = power(p, n * 10, MOD);
    k = (k * multiplier) % MOD;
    cout << k;
}
