#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main(){
    int n;
    cin >> n;
    char c;
    int directionX[4] = {1, 0, -1, 0};
    int directionY[4] = {0, -1, 0, 1}; // R일경우 index 증가, L일경우 index 감소
    int currentX = 0, currentY = 0;
    int directionIDX = 0;
    vector<pair<int, int>> coords;
    coords.push_back(make_pair(currentX, currentY));
    for(int i = 0; i < n; i++){
        cin >> c;
        if(c == 'R'){
            directionIDX++;
            directionIDX%=4;
        }
        else if(c == 'L'){
            directionIDX++;
            directionIDX++;
            directionIDX++;
            directionIDX%=4;
        }
        else if(c == 'F'){
            currentX += directionX[directionIDX];
            currentY += directionY[directionIDX];
            coords.push_back(make_pair(currentX, currentY));
        }
    }
    int miniX = 0;
    int miniY = 0;
    for(int i = 0; i < coords.size(); i++){
        if(coords[i].first < miniX){
            miniX = coords[i].first;
        }
        if(coords[i].second < miniY){
            miniY = coords[i].second;
        }
        // cout << coords[i].first << " " << coords[i].second << "\n";
    }
    int maxiX = 0;
    int maxiY = 0;
    map<pair<int, int>, int> sorted_coords;
    for(int i = 0; i < coords.size(); i++){
        coords[i].first -= miniX;
        coords[i].second -= miniY;
        if(coords[i].first > maxiX){
            maxiX = coords[i].first;
        }
        if(coords[i].second > maxiY){
            maxiY = coords[i].second;
        }
        sorted_coords[make_pair(coords[i].first, coords[i].second)] = 1;
    }
    for(int i = 0; i <= maxiX; i++){
        for(int j = 0; j <= maxiY; j++){
            if(sorted_coords[make_pair(i, j)] == 1){
                cout << ".";
            }
            else{
                cout << "#";
            }
        }
        cout << "\n";
    }
    return 0;
}