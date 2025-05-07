#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//최대 높이와 넓이를 곱하면 끝
int main()
{
    int N;
    cin >> N;
    int list[367]={0};  //366인 이유는 365에 들어있는 값 처리용 (누적합 배열)
    int st,en;
    for(int i=0;i<N;i++)
    {
        cin>>st>>en;
        for(int j=st;j<=en;j++) //시작과 끝사이 체크
        {
            list[j]++;
        }
    }
    int w=0;
    int h=0;
    int sum=0;   
    for(const auto& li:list)
    {
        if(li>0)        //값이 존재
        {
            if(h==0)    //이전 값이 없다면
            {
                w=1;
            }
            else
            {
                w++;
            }
            h=max(h,li);
        }
        else if(h>0)    //끝일경우 계산 후 초기화
        {
            sum+=w*h;   
            w=h=0;
        }
    }
    cout<<sum;
    return 0;
}
