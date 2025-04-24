#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;
struct phash
{
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        return hash<T1>()(p.first) ^ (hash<T2>()(p.second) << 1);
    }
};

class Pipe
{
private:
    unordered_map<pair<char, char>, int, phash> edges;      //언오더맵 간선(시작점,끝점 -> 용량)
    unordered_map<char, unordered_set<char>> near;          //언오더맵 노드(연결되어 있는 노드)
    vector<char> vist;

public:
    Pipe()
    {
        edges.clear();
        near.clear();
    }
    void add(char start, char dst, int val) // 병렬
    {
        if (start == dst)                                   //예외처리
            return;
        near[start].insert(dst);                            //노드 양방향추가
        near[dst].insert(start);
        edges[{start, dst}] += val;                         //간선 양방향추가
        edges[{dst, start}] += val;
    }
    int remove(char start, char dst)
    {
        pair<char, char> node = {start, dst};
        pair<char, char> rvnode = {dst, start};
        if (edges.find(node) != edges.end())                //간선이 있다면
        {
            int val = edges[node];                          //리턴용
            edges.erase(node);                              //간선 삭제
            edges.erase(rvnode);

            near[start].erase(dst);                         //노드에서 연결된 노드 삭제
            near[dst].erase(start);

            if (near[start].empty())                        //만약 더이상 연결된 노드가 없다면 삭제
            {
                near.erase(start);
            }
            if (near[dst].empty())
            {
                near.erase(dst);
            }
            return val;
        }
        return -1;
    }
    void wave(char node)
    {
        auto it = near[node].begin();                       //노드에 연결된 2개
        char n1 = *it;
        ++it;
        char n2 = *it;

        int v1 = remove(node, n1);                          //간선 삭제
        int v2 = remove(node, n2);
        add(n1, n2, min(v1, v2));                           //새로운 간선 생성 값은 둘중 최소값
    }
    void process()
    {
        bool changed;
        do
        {
            changed = false;
            vector<char> keys;
            for (const auto &p : near)                      //현재 존재하는 노드 key에 담기
            {
                keys.push_back(p.first);
            }

            for (char node : keys)
            {
                // 이전 단계에서 삭제되었을 수도 있으니 체크(A나 Z와 연결 안되어 있는 노드)
                if (near.find(node) == near.end())
                    continue;

                if (near[node].size() == 2 && !(node == 'A' || node == 'Z'))    //A나Z가 아니며, 간선이 2개 있는 노드 직렬병합
                {
                    wave(node);
                    changed = true;
                }
                else if (near[node].size() == 1 && !(node == 'A' || node == 'Z'))   //간선이 하나인 노드 삭제
                {
                    char neighbor = *near[node].begin();
                    remove(node, neighbor);
                    changed = true;
                }
            }

        } while (changed);              //변화가 없을 때까지
        cout << edges[{'A', 'Z'}];
    }
};

int main()
{
    Pipe p;
    int n;
    cin >> n;
    char a, b;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        cin >> x;
        p.add(a, b, x);
    }
    p.process();
    return 0;
}