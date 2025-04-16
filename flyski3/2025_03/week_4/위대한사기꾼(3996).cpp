#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

int main()
{
    long long n;
    int k,idx=0;
    cin >> n >>k;
    int list[51];
    while(n>0)
    {
        list[idx]=n%k;
        n=n/k;
        idx++;
    }
    for(int i=idx-1;i>=0;i--)
    {
        if(i%2==1&&list[i]>0)
        {
            for(int j=i;j>=0;j--)
            {
                list[j]=j%2==1?0:k-1;
            }
            break;
        }
    }
    int num=1;
    for(int i=0;i<idx;i+=2)
    {
       num+=list[i]*pow(k,i/2);
    }
    cout<<num;
    return 0;
}
