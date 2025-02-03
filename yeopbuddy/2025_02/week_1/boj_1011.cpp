#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int tc;
    cin >> tc;
    int x, y;
    int dist, mxnum, smnum, answer;
    for(int i = 0; i < tc; i++){
        cin >> x >> y;
        dist = y - x;
        mxnum = (int)sqrt(dist);
        smnum = (mxnum*(mxnum + 1)) / 2;

        if(2*smnum == dist){ // case 1
            answer = mxnum * 2;
        }
        else if(2*smnum < dist){ // case 2
            answer = mxnum * 2 + 1;
        }
        else{ // 2*smnum > dist
            if((2*smnum - dist) == mxnum){ // case 3
                answer = mxnum * 2 - 1;
            }
            else{ // case 1
                answer = mxnum * 2;
            }
        }
        cout << answer << "\n";
        // cout << (int)sqrt(y) << "\n";
    }
}