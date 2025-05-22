#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> p0; 
    vector<int> p1; 
    vector<int> p2;
    vector<int>::iterator it;
    
    for(int i = 0; i < n; i++){
        int num; 
        cin >> num; 
        int p = num % 3;
        switch(p){
            case 0: {
                p0.push_back(num);
                break;
            }
            case 1: {
                p1.push_back(num);
                break;
            }
            case 2: {
                p2.push_back(num);
                break;
            }
        }
    }
    
    
    int s0 = p0.size();
    int s1 = p1.size();
    int s2 = p2.size();
    
    if(s0 - 1 > s1 + s2){
        cout << "-1";
    }else if(s0 == 0 && (s1 != 0 && s2 != 0)){
        cout << "-1";
    }else{
        vector<int> ans;
        for(int i = 0; i < s1; i++){
            ans.push_back(p1[i]);
        }
        if(s0 != 0){
            ans.push_back(p0[s0 - 1]);
            p0.pop_back();
            s0--;
        }
        for(int i = 0; i < s2; i++){
            ans.push_back(p2[i]);
        }
        // for(int a : ans){
        //     cout << a << " ";
        // }
        // cout << "\n";
        while(s0 != 0){
            it = ans.begin();
            for(int i = 0; i < ans.size(); i++){
                if(i == 0){
                    if(ans[i] % 3 != 0){
                        ans.insert(it + i, p0[s0 - 1]);
                        p0.pop_back();
                        s0--;
                        break;   
                    }
                }
                else if(i == ans.size() - 1){
                    if(ans[i] % 3 != 0){
                        ans.push_back(p0[s0 - 1]);
                        p0.pop_back();
                        s0--;
                        break;
                    }
                }
                else if(ans[i] % 3 != 0 && ans[i + 1] % 3 != 0){
                    ans.insert(it + i + 1, p0[s0 - 1]);
                    p0.pop_back();
                    s0--;
                    break;
                }
                
            }
            // for(int a : ans){
            //     cout << a << " ";
            // }
            // cout << "\n";
        }
        for(int a : ans){
            cout << a << " ";
        }
    }
    
    return 0;
}