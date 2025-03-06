#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<long long> fluid(n, 0);
    for(int i = 0; i < n; i++){
        cin >> fluid[i];
    }
    sort(fluid.begin(), fluid.end());
    long long targetval = 0;
    long long answer = 3000000000;
    long long num1, num2, num3;
    for(int i = 0; i < n - 2; i++){
        int rightpointer = n - 1;
        int leftpointer = i + 1;
        while(leftpointer < rightpointer){
            long long val = fluid[i] + fluid[leftpointer] + fluid[rightpointer];
            if(abs(val) - targetval < answer){
                answer = abs(val) - targetval;
                num1 = fluid[i]; num2 = fluid[leftpointer]; num3 = fluid[rightpointer];
            }
            if(val < 0){
                leftpointer++;
            }
            else if(val > 0){
                rightpointer--;
            }
            else{
                cout << fluid[i] << " " << fluid[leftpointer] << " " << fluid[rightpointer];
                return 0;
            }
        }
    }
    cout << num1 << " " << num2 << " " << num3;
    return 0;
}