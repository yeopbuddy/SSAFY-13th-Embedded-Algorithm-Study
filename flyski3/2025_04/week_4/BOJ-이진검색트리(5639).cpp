#include <iostream>
#include <algorithm>
#define fastio               \
    ios::sync_with_stdio(0); \
    cout.tie(0);            \
    cin.tie(0);
using namespace std;
#define endl '\n';
/*
구조 이진검색
노드 n
left,right

입력
부모의 값보다 작다면 왼쪽에 넘기기
크다면 오른쪽에 넘기기
반복

출력 dfs
왼쪽으로 쭉 내려가다가 자식이 없으면 그때부터 출력
왼쪽 오른쪽 자신 순으로 출력
*/
struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val), left(nullptr),right(nullptr){}
};

void add(Node*& root,int val)
{
    if(root==nullptr)
    {
        root = new Node(val);
        return;
    }
    if(val<root->val)
    {
        add(root->left,val);
    }
    else
    {
        add(root->right,val);
    }
    return;
}
void printreaf(Node* root)
{
    if(root!=nullptr)
    {
        printreaf(root->left);
        printreaf(root->right);
        cout<<root->val<<endl;
    }
    
}
int main() {
    fastio;
    int n;
    Node* root = nullptr;
    while(cin>>n)
    {
        add(root,n);
    }
    printreaf(root);
    return 0;
}
