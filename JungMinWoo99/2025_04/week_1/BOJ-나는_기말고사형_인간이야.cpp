#include <iostream>
#define endl '\n'

#include <vector>
#include <algorithm>
#include <cctype>
#include <numeric>

#include <queue>

using namespace std;

struct SubjectStudy
{
    int val;
    int idx;
    
    bool operator<(const SubjectStudy& b) const
    {
        return this->val<b.val;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> subject_arr;
    priority_queue<SubjectStudy> sub_study_que;

    subject_arr.resize(M);
    for(auto& subject:subject_arr)
        cin>>subject;
    for(int idx=0;idx<M;idx++)
    {
        SubjectStudy sub_study;
        sub_study.idx = idx;
        cin >> sub_study.val;
        sub_study_que.push(sub_study);
    }

    for(int time = 0;time<N*24&&!sub_study_que.empty();time++)
    {
        auto most_high_effect = sub_study_que.top();
        
        if(100 - subject_arr[most_high_effect.idx] >= most_high_effect.val)
        {
            subject_arr[most_high_effect.idx] +=most_high_effect.val;
            if(subject_arr[most_high_effect.idx] == 100)
                sub_study_que.pop();
        }
        else
        {
            sub_study_que.pop();
            most_high_effect.val=100 - subject_arr[most_high_effect.idx];
            sub_study_que.push(most_high_effect);
            time--;
        }
    }

    int answer = 0;
    for(int score: subject_arr)
        answer+=score;

    cout<<answer<<endl;

    return 0;
}