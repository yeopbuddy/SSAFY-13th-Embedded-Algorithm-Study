#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> STUDENTS(n);
    vector<vector<tuple<int, int, int>>> DP(n + 1, vector<tuple<int, int, int>>(n));

    for (int i = 0; i < n; i++) {
        cin >> STUDENTS[i];
        DP[0][i] = { STUDENTS[i], STUDENTS[i], 0 };
    }
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < n - i; j++) {
            int NewMax = max(get<0>(DP[i - 1][j]), get<0>(DP[i - 1][j + 1]));
            int NewMin = min(get<1>(DP[i - 1][j]), get<1>(DP[i - 1][j + 1]));
            DP[i][j] = { NewMax, NewMin, NewMax - NewMin };
        }
    }

    vector<int> ANSDP(n, 0);
    
    for (int i = 1; i < n; i++) {
        int MaxVal = ANSDP[i - 1];
        for (int j = 0; j < i; j++) {
            if (j == 0) {
                MaxVal = max(get<2>(DP[i - j][j]) + ANSDP[0], MaxVal);
            }
            else {
                MaxVal = max(get<2>(DP[i - j][j]) + ANSDP[j - 1], MaxVal);
            }
        }
        ANSDP[i] = MaxVal;
    }
    cout << ANSDP[n-1];
    return 0;
}