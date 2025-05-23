#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct node
{
    int x, y;
};
bool cmp(const node &a, const node &b)
{
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
int main()
{
    vector<node> list;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int temp;
            cin >> temp;
            if (temp)
            {
                list.push_back({i, j});
            }
        }
    }
    sort(list.begin(), list.end(), cmp);
    if (list.size() == 2 * k)
    {
        cout << 0;
        return 0;
    }
    else if (list.size() == 2 * k - 1)
    {
        cout << 1 << endl;
        node temp = list[0];
        if (list.size() != 1)
        {
            int i = 2;
            if (list[1].x == temp.x)
            {
                for (; i < list.size(); i++)
                {
                    if (list[i].x != temp.x)
                    {
                        temp.y = list[i].y;
                        break;
                    }
                }
                if(i==list.size())
                {
                    temp.y=list[k-1].y;
                }
            }
            else
            {
                for (; i < list.size(); i++)
                {
                    if (list[i].y != temp.y)
                    {
                        temp.x = list[i].x;
                        break;
                    }
                }
                if(i==list.size())
                {
                    temp.x=list[k-1].x;
                }
            }
        }
        cout << temp.x << " " << temp.y << endl;
    }
    else 
    {
        int si = 2 * k - list.size();
        cout << si << endl;
        for (int i = k - si; i < k; i++)
        {
            cout << list[i].x << " " << list[i].y << endl;
        }
    }
    return 0;
}
