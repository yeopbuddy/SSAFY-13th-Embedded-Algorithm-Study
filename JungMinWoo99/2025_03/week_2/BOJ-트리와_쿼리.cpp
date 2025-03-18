#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

#include <queue>


using namespace std;

#define endl '\n'

class TreeDP
{
public:
    TreeDP(int N, int R) : root(R), abj_list(N+1),DP(N+1,1)
    {
        for(int edge_cnt = 0;edge_cnt<N-1;edge_cnt++)
        {
            int a, b;
            cin>>a>>b;
            abj_list[a].push_back(b);
            abj_list[b].push_back(a);
        }
    }

    int fillTreeDP(int node_num, int p_num){
        for(int abj: abj_list[node_num])
            if(abj != p_num)
                DP[node_num] += fillTreeDP(abj,node_num);
        return DP[node_num];  
    }

    void printDP()
    {
        for(int val:DP)
            cout<<val<<' ';
        cout<<endl;
    }

    int getAnswer(int node)
    {
        return DP[node];
    }

private:
    int root;
    vector<int> DP;
    vector<vector<int>> abj_list; 
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, R, Q;
    cin>> N>>R>>Q;
    TreeDP tree_dp(N,R);
    tree_dp.fillTreeDP(R,-1);
    //tree_dp.printDP();
    for(int q = 0;q<Q;q++)
    {
        int node;
        cin>> node;
        cout<<tree_dp.getAnswer(node)<<endl;
    }

    return 0;
}