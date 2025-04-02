#include <iostream>

int main()
{
    int N, M;
    std::cin>> N >> M;

    int dump;
    for(int i = 0;i<8;i++)
        std::cin >>dump;

    if(N+M==3)
        std::cout<<"ChongChong"<<'\n';
    else
        std::cout<<"GomGom"<<'\n';

    return 0;
}