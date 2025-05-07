#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

#define SHAPE_NUM 3

using namespace std;

class ShapeSort{
public:
    ShapeSort(int N):N(N),input(N), shape_order(SHAPE_NUM),shape_cnt(SHAPE_NUM+1,0){
        for(auto& ele: input){
            cin>>ele;
            shape_cnt[ele]++;
        }

        for(int idx = 0;idx<3;idx++){
            shape_order[idx] = idx+1;
        }
    }

    bool NextOrder(){
        return next_permutation(shape_order.begin(), shape_order.end());
    }

    int getSortCnt(){
        vector<vector<int>> shape_cnt_mat(SHAPE_NUM+1,vector<int>(SHAPE_NUM+1,0));

        int input_idx = 0;
        for(int idx = 0; idx < SHAPE_NUM;idx++){
            for(int idx2=0;idx2<shape_cnt[shape_order[idx]];idx2++){
                shape_cnt_mat[shape_order[idx]][input[input_idx++]]++;
            }
        }


        // for(auto ele: shape_order)
        //     cout<<ele<<' ';
        // cout<<endl;
        // for(auto row: shape_cnt_mat){
        //     for(auto ele: row)
        //         cout<<ele<<' ';
        //     cout<<endl;
        // }
        
        int ret = 0;
        int sub = 0;
        for(int shape_group = 1;shape_group<=SHAPE_NUM;shape_group++){
            for(int shape = 1;shape<=SHAPE_NUM;shape++){
                if(shape_order[shape_group-1] == shape)
                    continue;
                int max_val = max(shape_cnt_mat[shape_order[shape_group-1]][shape],shape_cnt_mat[shape][shape_order[shape_group-1]]);
                int min_val = min(shape_cnt_mat[shape_order[shape_group-1]][shape],shape_cnt_mat[shape][shape_order[shape_group-1]]);
                ret+=max_val;
                sub=max_val-min_val;
            }
        }

        ret = ret / 2 - sub;

        return ret;
    }
private:
    int N;
    vector<int> input;
    vector<int> shape_order;//shape_order[idx]: idx+1 도형의 순번
    vector<int> shape_cnt;
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    cin >> N;
    ShapeSort ss(N);
    int answer = numeric_limits<int>::max();
    do{
        answer = min(answer,ss.getSortCnt());
    }while(ss.NextOrder());

    cout<<answer<<endl;
    return 0;
}