#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int arr[500][500] = {0};
int n, m;
// sky-blue
int dx1_1[4] = {0,0,0,0}; int dy1_1[4] = {0,1,2,3};
int dx1_2[4] = {0,1,2,3}; int dy1_2[4] = {0,0,0,0};

// yellow
int dx2[4] = {0,0,1,1}; int dy2[4] = {0,1,0,1};

// orange
int dx3_1[4] = {0,0,1,2}; int dy3_1[4] = {0,1,0,0};
int dx3_2[4] = {0,0,1,2}; int dy3_2[4] = {0,1,1,1};
int dx3_3[4] = {0,0,0,1}; int dy3_3[4] = {0,1,2,2};
int dx3_4[4] = {0,0,0,1}; int dy3_4[4] = {0,1,2,0};
int dx3_5[4] = {0,1,2,2}; int dy3_5[4] = {0,0,0,-1};
int dx3_6[4] = {0,1,2,2}; int dy3_6[4] = {0,0,0,1};
int dx3_7[4] = {0,1,1,1}; int dy3_7[4] = {0,0,1,2};
int dx3_8[4] = {0,0,0,-1}; int dy3_8[4] = {0,1,2,2};

// green
int dx4_1[4] = {0,1,1,2}; int dy4_1[4] = {0,0,1,1};
int dx4_2[4] = {0,1,1,2}; int dy4_2[4] = {0,0,-1,-1};
int dx4_3[4] = {0,0,-1,-1}; int dy4_3[4] = {0,1,1,2};
int dx4_4[4] = {0,0,1,1}; int dy4_4[4] = {0,1,1,2};

// pink
int dx5_1[4] = {0,-1,0,1}; int dy5_1[4] = {0,1,1,1};
int dx5_2[4] = {0,1,1,1}; int dy5_2[4] = {0,-1,0,1};
int dx5_3[4] = {0,1,1,2}; int dy5_3[4] = {0,0,1,0};
int dx5_4[4] = {0,0,0,1}; int dy5_4[4] = {0,1,2,1};

int findmaxval(int x, int y){
    
    int rtnval = 0;
    int mxval = 0;
    
    for(int i = 0; i < 4; i++){
        int nx = x + dx1_1[i];
        int ny = y + dy1_1[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx1_2[i];
        int ny = y + dy1_2[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx2[i];
        int ny = y + dy2[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_1[i];
        int ny = y + dy3_1[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_2[i];
        int ny = y + dy3_2[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_3[i];
        int ny = y + dy3_3[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_4[i];
        int ny = y + dy3_4[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_5[i];
        int ny = y + dy3_5[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_6[i];
        int ny = y + dy3_6[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_7[i];
        int ny = y + dy3_7[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx3_8[i];
        int ny = y + dy3_8[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx4_1[i];
        int ny = y + dy4_1[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx4_2[i];
        int ny = y + dy4_2[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx4_3[i];
        int ny = y + dy4_3[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx4_4[i];
        int ny = y + dy4_4[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx5_1[i];
        int ny = y + dy5_1[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx5_2[i];
        int ny = y + dy5_2[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx5_3[i];
        int ny = y + dy5_3[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    
    mxval = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx5_4[i];
        int ny = y + dy5_4[i];
        if(0 <= nx && nx < n && 0 <= ny && ny < m){
            mxval += arr[nx][ny];
        }
        else{
            mxval = 0;
            break;
        }
    }
    if(rtnval < mxval){
        rtnval = mxval;
    }
    return rtnval;
}


int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }
    int maxv = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (findmaxval(i, j) > maxv){
                maxv = findmaxval(i, j);
            }
        }
    }
    cout << maxv;
}