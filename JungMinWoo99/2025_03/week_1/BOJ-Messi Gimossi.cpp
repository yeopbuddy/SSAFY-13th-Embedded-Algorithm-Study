#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <queue>
#define endl '\n'
using namespace std;

//풀이 과정
/*
1. 사전에 문자열 길이가 int 범위 내인 messi의 길이를 DP로 계산
2. 다음과 같은 과정을 통해 M과 N을 축소시킴
    2-0. length(messi(N-1)) < M <= length(messi(N))인 N 찾기
        => M번째 글자는 messi(N)에 있음
    2-1. M < messi(N-1) 인 경우
        M번째 글자는 messi(N-1)에 속함
            => M = M, N= N-1로 바꾸고 2과정을 반복
    2-2. M == messi(N-1) 인 경우
        M번째 글자는 공백
            => messi(N)은 messi(N-1), 공백, messi(N-2)이기 때문
    2-3. M > messi(N-1) 인 경우
        M번째 글자는 messi(N-2)에 속함
            => M = M - messi(N-1) - 1(공백때문에), N= N-2로 바꾸고 2과정을 반복
3. 2과정을 N이 1또는 0이 될 때까지 반복
*/

//문제는 인덱스 1부터 시작이지만 messi(0)을 Gimossi로 해도 됨
string MG0 = "Gimossi";
string MG1 = "Messi";

vector<long long> MG;

long long MessiGimossi(int N)
{
    if (MG[N] != 0)
        return MG[N];
    // messi(N-1), 공백, messi(N-2)을 차례로 이어붙임
    MG[N] = MessiGimossi(N - 1) + 1 + MessiGimossi(N - 2); 
    return MG[N];
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    MG.push_back(MG0.length());
    MG.push_back(MG1.length());


    int max_n = 2;
    while (MG.back() < numeric_limits<int>::max()) // 2^30-1을 벗어날때까지 계산
    {
        MG.push_back(0);
        MessiGimossi(max_n);
        max_n++;
    }

    int M;
    cin >> M;

    int idx = 1;
    while (MG[idx] <= M)
        idx++;

    char charM;
    while (true)
    {
        if (idx == 0)
        {
            charM = MG0[M - 1];
            break;
        }
        else if (idx == 1)
        {
            charM = MG1[M - 1];
            break;
        }

        if (MG[idx - 1] >= M)
            idx = idx - 1;
        else if (MG[idx - 1] + 1 == M)
        {
            charM = ' ';
            break;
        }
        else
        {
            M -= (MG[idx - 1] + 1); // 공백 포함하여 빼야됨
            idx = idx - 2;
        }
    }

    if (charM == ' ')
        cout << "Messi Messi Gimossi" << endl;
    else
        cout << charM << endl;

    return 0;
}