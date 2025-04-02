/*
트리 DP를 통한 문제 풀이
dp(node): node의 모든 (간접 포함)부하들에게 뉴스를 전달하기 위한 최소 시간
dp(parent) = max(dp(children[i]+i)) (i는 i번째 접근하는 자식 노드)
children의 순서는 dp(children[i])가 큰 순서대로 접근하는 것이 자명함
*/
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int dp_val = 0;
    vector<Node *> children;

    struct compNodePtr
    {
        bool operator()(const Node *a, const Node *b)
        {
            return a->dp_val > b->dp_val;
        }
    };

    void sortChildren()
    {
        sort(children.begin(), children.end(), compNodePtr());
    }
};

class Tree
{
public:
    Tree(int N) : N(N), employees(N) {}

    void inputTree()
    {
        for (int i = 0; i < N; i++)
        {
            int boss;
            cin >> boss;
            if (boss != -1)
                employees[boss].children.push_back(&employees[i]);
        }
    }

    void fillDP(Node *p = nullptr)
    {
        if(p == nullptr)
            p = &employees[0];
        if (p->children.empty())
            return;
        for (auto &child : p->children)
            fillDP(child);
        p->sortChildren();
        for (int idx = 0; idx < p->children.size(); idx++)
            p->dp_val = max(p->dp_val, p->children[idx]->dp_val + (idx + 1));
    }

    void printAnswer()
    {
        cout<<employees[0].dp_val<<endl;
    }

private:
    int N;
    vector<Node> employees;
};

int main(void)
{
    int N;
    cin >> N;
    Tree tree(N);
    tree.inputTree();
    tree.fillDP();
    tree.printAnswer();

    return 0;
}