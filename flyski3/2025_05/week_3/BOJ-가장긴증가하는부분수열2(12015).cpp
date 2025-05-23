#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int arr[1000001];
int main()
{
    arr[0] = 0;
    int n, idx = 0; // idx = 현재 가장 긴 길이
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        if (arr[idx] < temp) // 가장 긴 길이의 수보다 큰 경우
        {
            idx++;
            arr[idx] = temp;
        }
        else
        {
            auto it = lower_bound(arr, arr + idx, temp); // temp보다 작은 수의 위치 다음 수
            arr[it - arr] = temp;                        // 갱신
        }
    }
    cout << idx;
    return 0;
}
