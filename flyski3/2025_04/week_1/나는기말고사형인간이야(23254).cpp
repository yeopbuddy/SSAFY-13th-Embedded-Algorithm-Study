#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct node
{
    int score;
    int efficiency;
};
struct cmp
{
    int operator()(node left, node right) const
    {

        if (left.efficiency == right.efficiency)
            return left.score < right.score;
        return left.efficiency < right.efficiency;
    }
};
priority_queue<node, vector<node>, cmp> pq;
int main()
{
    int n, m, num = 0;
    cin >> n >> m;
    n *= 24;
    vector<node> list(m);
    for (int i = 0; i < m; i++)
    {
        cin >> list[i].score;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> list[i].efficiency;
    }
    for (auto &li : list)
    {
        pq.push(li);
    }
    
    node x = pq.top();
    pq.pop();
    while (n > 0)
    {
        if (x.score + x.efficiency > 100)
        {
            if(pq.empty())
            {
                cout<<num+100;
                return 0;
            }
            x.efficiency = 100 - x.score;
            if (pq.top().efficiency > x.efficiency)
            {
                pq.push(x);
                n++;
            }
            else
            {
                num+=100;
            }
            x=pq.top();
            pq.pop();
        }
        else
        {
            x.score += x.efficiency;
        }
        n--;
    }
    num+=x.score;
    while(!pq.empty())
    {
        num+=pq.top().score;
        pq.pop();
    }
    cout<<num;
    return 0;
}