#include <iostream>
#include <vector>
using namespace std;
int maxy=1000000;
void co(vector<int> li,vector<int> cmpli,int n)
{
    int abc[4][4]={0};
    int cont=0;
    for(int i=0;i<n;i++)
    {
        if(li[i]!=cmpli[i])
        {
            if(abc[cmpli[i]][li[i]]>0)
            {
                cont++;
                abc[cmpli[i]][li[i]]--;
            }
            else
                abc[li[i]][cmpli[i]]++;
        }
    }
    if(abc[1][2]>0)
    {
        cont+=(abc[1][2]*2);
    }
    else if(abc[1][3]>0)
    {
        cont+=(abc[1][3]*2);
    }
    maxy=min(maxy,cont);
    return;
}
void crli(int* cont,vector<int>& cmpli,int* abc,int n)
{
    int idx=0;
    for(int j=0;j<3;j++)
        for(int i=0;i<cont[abc[j]];i++,idx++)
            cmpli[idx]=abc[j];
    return;
}
int main()
{
    int n;
    cin >> n;
    vector<int> li(n);
    vector<int> cmpli(n);
    int cont[4]={0};
    for(int i=0;i<n;i++)
    {
        cin>>li[i];
        cont[li[i]]++;
    }
    int abc[6][3] = {
    {1, 2, 3},
    {1, 3, 2},
    {2, 1, 3},
    {2, 3, 1},
    {3, 1, 2},
    {3, 2, 1}
    };
    for(int i=0;i<6;i++)
    {
        crli(cont,cmpli,abc[i],n);
        co(li,cmpli,n);
    }
    cout<<maxy;
    return 0;
}
