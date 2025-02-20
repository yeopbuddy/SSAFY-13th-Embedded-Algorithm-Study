#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(int argc, char** argv){
    int n;
    cin >> n;
    vector<vector<int>> lecture (n, vector<int>(2, 0));
    int t1, t2;
    for(int i = 0; i < n; i++){
        cin >> t1 >> t2;
        lecture[i][0] = t2, lecture[i][1] = t1;
    }
    // if save the [[t1, t2], [t1, t2]] and
    // sort(begin, end, compare) -> compare(vec a, vec b){return a[1] < b[1]}
    // causing time out ..
    sort(lecture.begin(), lecture.end());
    int answer = 1;
    int endtime = lecture[0][0];
    for(int i = 0; i < n; i++){
        if(endtime <= lecture[i][1]){
            answer++;
            endtime = lecture[i][0];
        }
    }
    cout << answer;
}