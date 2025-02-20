#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char** argv){
    vector<long int> vec;
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        float num;
        cin >> num;
        if (i == 0){
            vec.push_back(num);    
        }
        else{
            vec.push_back(vec[vec.size()-1] + num);    
        }
        
    }
    for(int i = 0; i < k; i++){
        float n1, n2;
        cin >> n1 >> n2;
        if (n1 == 1){
            cout << vec[n2-1]/n2 << endl;
        }
        else{
            cout << (vec[n2-1] - vec[n1-2])/(n2 - n1 + 1) << endl;
        }
    }
    // 10 60 80 150 250
}