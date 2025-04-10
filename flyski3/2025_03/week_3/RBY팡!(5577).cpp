#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
vector<int> list;
int boom(vector<int>& copy, int idx,bool st)        //st 0은 idx>0방향, 1은 idx>n방향
{
    int nx=1;
    if(st?st==n:st==1)                              //끝이면 탐색x
    {
        return 0;
    }
    while(copy[st?idx+nx:idx-nx]==copy[idx])        //값이 같다면 더 멀리 탐색
    {
        nx++;
    }
    return nx;
}
int boom2(vector<int> copy,int idx, int num)
{
    int prv,nx,left,right;
    prv=nx=idx;
    copy[idx]=num;
    while(1)
    {
        left=boom(copy,prv,0);                     //st 0
        right=boom(copy,nx+1,1);                    //st 1
        if((copy[prv]!=copy[nx+1])||(left+right<4))         //두 공의 값이 다르거나, 총 합이 4미만일 경우 종료
        {
            return n-nx+prv;
        }
        prv-=left;
        nx+=right;
    }
    return 0;
}
int change(vector<int>& copy, int idx)
{
    int left,right;
    left=copy[idx-1];
    right=copy[idx+1];
    if(!left)                   //왼쪽 공이 없다면 오른공으로
    {
        return boom2(copy,idx,right);
    }
    else if(!right)             //오른 공이 없다면 왼공으로
    {
        return boom2(copy,idx,left);
    }
    else
    {
        int temp = boom2(copy,idx,right); //둘중 최소값
        if(left!=right)
        {
            temp = min(temp,boom2(copy,idx,left));
        }
        return temp;
    }
    return 0;
}
int main()
{
    cin >> n;
    list.resize(n+2);           //양 끝 0
    for (int i = 1; i <= n; i++)
    {
        cin >> list[i];
    }
    if(n==1)                    //1일경우 종료
    {
        cout<<1;
        return 0;
    }
    int mincount=n+1;
    for(int i=1;i<=n;i++)
    {
        mincount=min(mincount,change(list,i));
    }
    cout<<mincount;
    return 0;
}
/*
0부터 n까지 전후가 다른 idx를 함수로 호출
해당 idx값을 다른 값으로 변경 후

idx를 기준으로 서로 멀어지면서 차이 계산
차이가 4미만일경우 계산전 값을 이용하여 남은수 구하기
이상일 경우 차이 계산부터 반복

만약 idx 값이 다를경우 스탑

전후를 계산하기 때문에 맨 처음과 마지막에 더미값(0)
만약 첫번째나 마지막일경우 더미값을 제외한 값 선택

1   1
1   2

2   4

1   5

1   6

3   9

2   11

1   12


1+3+1
2+2

*/