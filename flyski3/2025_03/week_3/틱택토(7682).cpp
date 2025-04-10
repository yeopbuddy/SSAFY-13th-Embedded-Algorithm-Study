#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool bingo(string list)             //3개 받아서 같은지 확인
{
    if (list[0] == list[1] && list[0] == list[2])
    {
        return true;
    }
    return false;
}
void chk(string str, vector<char> &flag)        //3개 같으면 열or행에 (O,x)추가
{
    if (str[0] != '.' && bingo(str))
    {
        flag.push_back({str[0]});
    }
    return;
}
void ttk(string str)
{
    vector<char> row;
    vector<char> column;
    string text;
    int x = 0;
    int o = 0;
    for (int i = 0; i < 9; i++)                     //ox 개수확인
    {
        if (str[i] == 'X')
            x++;
        else if (str[i] == 'O')
            o++;
    }
    for (int i = 0; i < 3; i++)                         //chk
    {
        text = str[i];
        text += str[i + 3];
        text += str[i + 6];
        chk(str.substr(i * 3, 3), row);
        chk(text, column);
    }
    if (row.size() > 1 || column.size() > 1) // 행or열의 빙고 횟수가 2이상
    {
        cout << "invalid";
        return;
    }
    else if (row.size() == 0 && column.size() == 0)
    {
        // 대각선 없으면 invalid
        // 다만 9개 다찬상태에서는 valid
        text = str[0];
        text += str[4];
        text += str[8];
        chk(text, column);

        text = str[2];
        text += str[4];
        text += str[6];
        chk(text, column);
        if (column.size() == 0)     //대각도 없을때
        {
            if (x ==5&&o==4)
            {
                cout << "valid";
                return;
            }
            cout << "invalid";
            return;
        }
    }
    // x일경우 x개수=o개수+1;
    // o일경우 x개수=o개수;
    char key = row.size() > 0 ? row[0] : column[0];
    if ((key == 'X' && x != o + 1) || (key == 'O' && x != o))
    {
        cout << "invalid";
        return;
    }
    cout << "valid";
    return;
}
int main()
{
    string ticktack;
    while (1)
    {
        cin >> ticktack;
        if (ticktack == "end")
        {
            return 0;
        }
        ttk(ticktack);
        cout << endl;
    }
    return 0;
}
/*
조건
빙고 존재
행에서 빙고나온경우 다른 행에서 빙고 X
열도 마찬가지

o빙고인경우 x=o
빙고가 없거나 x빙고인경우 x= o-1

1. 빙고 탐색 X or O, 어느 행/열에서 빙고인지
2. 빙고조건 확인
3. OX개수 확인
*/