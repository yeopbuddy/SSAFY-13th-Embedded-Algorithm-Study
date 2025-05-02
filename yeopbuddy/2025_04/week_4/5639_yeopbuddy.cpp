#include <iostream>
using namespace std;

bool visit[1000000];

struct Node{
    int data;
    Node* parent;
    Node* left;
    Node* right;
};

class BTree{
    private:
        Node* root;
    public:
        BTree(){
            root = nullptr;
        }
        void insert(int node){
            Node* New = new Node;
            New->data = node;
            if(root == nullptr){ // 빈 트리일 경우 : 현재 insert를 루트 노드로 설정
                New->parent = nullptr;
                New->left = nullptr;
                New->right = nullptr;
                root = New;
                return;
            }
            Node* current = root; // 탐색할 위치 찾을 변수 : root부터 탐색
            while(true){
                if(New->data > current->data){ // insert할 값이 현재 탐색 중인 노드의 값보다 클 경우
                    if(current->right == nullptr){ // 현재 탐색 중인 노드의 오른쪽 노드가 비어있으면 : 그곳에 삽입
                        current->right = New;
                        New->parent = current;
                        New->left = nullptr;
                        New->right = nullptr;
                        return;
                    }
                    current = current->right; // 아니면 (현재 탐색 중인 노드의 오른쪽 노드가 비어있지 않으면) : 오른쪽으로 탐색
                }
                else{ // insert할 값이 현재 탐색 중인 노드의 값보다 작은 경우(같은 경우는 문제에 없다고 나와있음)
                    if(current->left == nullptr){ // 현재 탐색 중인 노드의 왼쪽 노드가 비어있으면 : 그곳에 삽입
                        current->left = New;
                        New->parent = current;
                        New->left = nullptr;
                        New->right = nullptr;
                        return;
                    }
                    current = current->left; // 아니면 (현재 탐색 중인 노드의 왼쪽 노드가 비어있지 않으면) : 왼쪽으로 탐색
                }
            }
        }
        void print(){ // 후위순회 코드 : 좌 > 우 > 루트 순
            Node* current = root;
            while(true){
                if(current->left != nullptr && !visit[current->left->data]){ // 왼쪽으로 탐색이 가능하면
                    current = current->left; // 왼쪽으로 탐색 (후위 순회의 우선순위가 왼쪽이 가장 우선이므로)
                }
                else{ // 왼쪽 노드가 없거나, 이미 방문 한 경우 : 본인을 출력할지, 아니면 오른쪽 노드로 들어갈지?
                    if(current->right != nullptr && !visit[current->right->data]){ // 오른쪽 노드 팀색이 가능하면?
                        current = current->right; // 오른쪽으로 탐색 (후위 순회의 우선순위가 오른쪽이 루트보다 우선이므로)
                    }
                    else{ // 왼쪽 노드 탐색도 불가능하고, 오른쪽도 탐색이 불가능할 경우 : 출력하고 상위 노드로 탐색 재개
                        cout << current->data << "\n"; 
                        visit[current->data] = true; // 출력 후 방문 처리
                        if(current->parent == nullptr){ // 이 경우는 루트 노드 : while문 종료
                            break;
                        }
                        current = current->parent; // 상위 노드로 탐색 재개
                    }
                }
            }
        }
};



int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int node;
    BTree* btree = new BTree();
    while(cin >> node){
        btree->insert(node);
    }
    btree->print();
    return 0;
}