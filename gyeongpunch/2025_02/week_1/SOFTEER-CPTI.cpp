#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main(int argc, char** argv){
    int N, M;
    cin >> N >> M;
    unordered_map<int, int> cpti_map;
    for(int i=0; i<N; i++){
        string str;
        cin >> str;
        int num = stoi(str, nullptr, 2);
        cpti_map[num]++;
    }
    cout << endl;
    int result = 0;

    for(const auto& bitmask : cpti_map){
        int cnt = bitmask.second;
        result += cnt*(cnt-1)/2;

        for(int i=0; i<M; i++){
            int one_bit_change = bitmask.first ^ (1<<i);
            if(cpti_map.count(one_bit_change)>0 && one_bit_change < bitmask.first){
                result += cnt * cpti_map[one_bit_change];
            }
            for(int j=i+1; j<M; j++){
                int two_bit_change = bitmask.first ^ (1<<i) ^ (1<<j);
                if(cpti_map.count(two_bit_change)>0 && two_bit_change < bitmask.first){
                    result += cnt * cpti_map[two_bit_change];
                }
            }
        }
    }

    cout << result << '\n';
    
    return 0;
}