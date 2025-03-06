#include <iostream>
#include <vector>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cin.tie(0);
using namespace std;
struct xy
{
    int x;
    int y;

    bool operator==(const xy &other) const              //==비교
    { 
        return x == other.x && y == other.y;
    }
    bool operator<(const xy &other) const               // sort
    { 
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};
xy I;                                                   //I위치
vector<xy> R;                                           //R위치
vector<vector<char>> map;
int mx, my;
int dxy[10][2] = {                                     // 입력 받은 번호에 대해 움직임
    0, 0,                                              // 더미
    1, -1,
    1, 0,
    1, 1,
    0, -1,
    0, 0,
    0, 1,
    -1, -1,
    -1, 0,
    -1, 1};

void chkmap() // 출력
{
    map[I.x][I.y] = 'I';                                // I 표시
    for (const auto &r : R)                             // R 표시
    {
        map[r.x][r.y] = 'R';
    }
    for (int i = 0; i < mx; i++)                        // 프린트 맵
    {
        for (int j = 0; j < my; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}

bool Imove(int st)
{
    I.x += dxy[st][0];                                  //I st 기준으로 이동
    I.y += dxy[st][1];
    // cout<<I.x<<" "<<I.y<<endl;
    for (auto &r : R)                                   // R움직임
    {
        if (I.x < r.x)
            r.x--;
        else if (I.x > r.x)
            r.x++;
        if (I.y < r.y)
            r.y--;
        else if (I.y > r.y)
            r.y++;
    }
    if (R.size() > 1)                                   // R이 2개 이상일시 중복확인 필요
    {
        sort(R.begin(), R.end());
        R.push_back({10000, 10000});                    //중복용 더미
        xy re = {10000, 10000};                         //중복용 더미2
        int flag = 0;
        for (auto r = R.begin(); r != R.end();)         //R반복문
        {
            if (*r == I)                                //I를 잡았을시 TRUE 리턴
            {
                return 1;
            }
            if (*r == re)                               //만약 같으면 
            {
                flag = 1;                               //나중에 re도 지우겠다는 의미
                r = R.erase(r);                         //R 삭제
            }
            else
            {
                re = *r;                                //같지 않다면 re를 갱신
                if (flag)                               //R을 삭제한 적이 있다면 re였던 것도 삭제
                {                                       //더미 2 : flag=1인 상태로 끝나는것 방지
                    r = R.erase(r - 1); 
                    flag = 0;
                }
                ++r;
            }
        }
        R.pop_back();                                   //더미 2 삭제제
    }
    else if(R.size())                                   //R이 하나라면 I를 잡는것만 확인
    {
        if(R[0]==I)
            return 1;
    }
    return 0;
}
int main()
{
    fastio;
    cin >> mx >> my;
    map.resize(mx, vector<char>(my, '.'));              //맵은 기본으로 '.'
    char x;

    for (int i = 0; i < mx; i++)
    {
        for (int j = 0; j < my; j++)
        {
            cin >> x;                                   //I or R 확인 나머지는 무시
            if (x == 'I')
            {
                I.x = i;
                I.y = j;
            }
            else if (x == 'R')
            {
                R.push_back({i, j});
            }
        }
    }
    string str;
    cin >> str;
    for (int i = 0; i < str.length(); i++)
    {
        int num = str[i] - '0';
        if (Imove(num))                                 //TRUE 리턴시 I를 잡았다는 의미
        {
            cout << "kraj " << i + 1;
            return 0;
        }
    }
    chkmap();

    return 0;
}