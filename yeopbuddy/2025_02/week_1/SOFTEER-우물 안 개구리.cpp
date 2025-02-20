#include<iostream>
#include<vector>
using namespace std;
int main(int argc, char** argv){
    int n, m, num1, num2;
    cin >> n >> m;
    vector<int> arr(n);
    vector<vector<int>> gym(n);
    for(int i = 0; i < n; i++){
        cin >> num1;
        arr[i] = num1;
    }
    for(int i = 0; i < m; i++){
        cin >> num1 >> num2;
        gym[num1-1].push_back(num2-1);
        gym[num2-1].push_back(num1-1);
    }
    int answer = 0;
    bool thebest;
    for(int i = 0; i < n; i++){
        thebest = true;
        for(int j = 0; j < gym[i].size(); j++){
            if(arr[gym[i][j]] >= arr[i]){
                thebest = false;
                break;
            }
        }
        if(thebest){
            answer++;
        }
    }
    cout << answer;
}