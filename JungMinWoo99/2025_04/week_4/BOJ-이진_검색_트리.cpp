#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

class BSF{
public:
    BSF():cur_idx(0){
        int in;
        while(cin>>in)
            input.push_back(in);
    }

    void PrintTree(){
        PrintTree(0,input.size());
    }

    void PrintTree(int tree_start, int tree_end){
        if(tree_start == tree_end) 
            return;

        int root = input[tree_start];
        int left_start = tree_start+1;
        int right_start = distance(input.begin(), upper_bound(input.begin()+left_start,input.begin()+tree_end,root));
        
        PrintTree(left_start, right_start);
        PrintTree(right_start, tree_end);
        cout<<root<<endl;;
    }
private:
    vector<int> input;
    int cur_idx;
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    BSF bsf;
    bsf.PrintTree();

    return 0;
}