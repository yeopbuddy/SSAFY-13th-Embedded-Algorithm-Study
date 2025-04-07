#include <iostream>
#define endl '\n';

#include <vector>
#include <limits>
#include <algorithm>

#include <cmath>
#include <deque>

using namespace std;

using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    vector<ll> digits; // idx번째 자리수 저장
    while (n != 0)
    {
        digits.push_back(n % k);
        n /= k;
    }

    if (digits.size() % 2 == 1)
        digits.push_back(0);

    deque<ll> even_th_digits;

    // for(int digit:digits)
    //     cout<<digit;
    // cout<<endl;

    bool is_up = false;
    for (int idx = digits.size() - 1; idx > -1; idx--)
    {
        if (idx % 2 == 0)
        {
            if (digits[idx + 1] != 0)
                is_up = true;

            if (!is_up)
                even_th_digits.push_front(digits[idx]);
            else
                even_th_digits.push_front(k - 1);
        }
    }

    // for(int digit:even_th_digits)
    //     cout<<digit;
    // cout<<endl;

    ll power = 1;
    ll sum = 0;
    for (int idx = 0; idx < even_th_digits.size(); idx++)
    {
        if (idx == 0)
            sum++;
        sum += (even_th_digits[idx]) * power;
        power *= k;
    }

    cout << sum << endl;

    return 0;
}