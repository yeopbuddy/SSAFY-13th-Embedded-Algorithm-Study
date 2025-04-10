#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1000001

int main(void)
{
    int M, N;
    cin>>M>>N;
    vector<int> is_prime(MAX,1);
    vector<int> prime;

    for(int i = 2;i<MAX;i++)
    {
        if(!is_prime[i])
            continue;
        prime.push_back(i);
        int mul = i;
        while(mul<MAX)
        {
            is_prime[mul] = 0;
            mul += i;
        }
    }

    for (int p : prime)
        if(M<=p&&p<=N)
            cout<<p<<endl;

    return 0;
}