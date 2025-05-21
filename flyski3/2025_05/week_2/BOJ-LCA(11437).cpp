#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define fastio               \
    ios::sync_with_stdio(0); \
    cout.tie(0);             \
    cin.tie(0);
using namespace std;
#define endl '\n';
struct node
{
    int n;
    int height;
    node *parent[20];
    vector<node *> children;
    node(int n) : n(n), height(0) { fill(parent, parent + 20, nullptr); }
};
void connect(node *parent, node *children)
{
    children->parent[0] = parent;
    children->height = parent->height + 1;
    for(int i=1;i<20;i++)
    {
        if(children->parent[i-1])
        {
            children->parent[i]=children->parent[i-1]->parent[i-1];
        }
        else
        {
            break;
        }
    }
}
void bfs(vector<node*>& nodes)
{
    queue<node*> qu; 
    vector<int> visited(nodes.size(), false); 
    visited[1]=1;
    qu.push(nodes[1]);
    while(!qu.empty())
    {
        node* parent =qu.front();
        qu.pop();
        for(auto li:parent->children)
        {
            if(!visited[li->n])
            {
                visited[li->n]=1;
                connect(parent,li);
                qu.push(li);
            }
        }
    }
}
int cmp(const vector<node*>& nodes,int diff,int a,int b) //a>b & diff>0
{
    int temp=0;
    while(diff>0)
    {
        if(diff&1)
        {
            a=nodes[a]->parent[temp]->n;
        }
        temp++;
        diff>>=1;
    }
    if(a==b) return a;

    for (int i = 19; i >= 0; i--) 
    {
        if (nodes[a]->parent[i] != nodes[b]->parent[i]) 
        {
            a = nodes[a]->parent[i]->n;
            b = nodes[b]->parent[i]->n;
        }
    }

    return nodes[a]->parent[0]->n;

}
int main()
{
    fastio;
    int n, m, a, b;
    cin >> n;
    vector<node *> nodes(n + 1);
    for (int i = 1; i <= n; i++)
    {
        nodes[i] = new node(i);
    }
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        nodes[a]->children.push_back(nodes[b]);
        nodes[b]->children.push_back(nodes[a]);
    }
    for(int i=0;i<20;i++)
        nodes[1]->parent[i]=nodes[1];
    bfs(nodes);
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        if(nodes[a]->height>nodes[b]->height)
        {
            cout<<cmp(nodes,nodes[a]->height-nodes[b]->height,a,b);    
        }
        else
        {
            cout<<cmp(nodes,nodes[b]->height-nodes[a]->height,b,a);
        }
        cout<<endl;
    }
    return 0;
}
