#include <iostream>
#define endl '\n'

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;
using ll = long long;

constexpr ll DIV=1'000'000'007;


class Mat
{
public:
    Mat(ll n):mat(n,vector<ll>(n,0)),N(n){}

    vector<ll>& operator[](ll idx)
    {
        return mat[idx];
    }

    const vector<ll>& operator[](ll idx) const
    {
        return mat[idx];
    }

    Mat operator*(const Mat& b)
    {
        Mat ret(N);
        for(ll r = 0;r<N;r++){
            for(ll c = 0; c<N;c++){
                for(ll idx = 0;idx<N;idx++){
                    ret[r][c] += (*this)[r][idx] * b[idx][c];
                    ret[r][c] %= DIV;
                }
            }
        }
        return ret;
    }

private:
    ll N;
    vector<vector<ll>> mat;
};

Mat MatPower(const Mat& x, ll y){
    if(y == 1)
        return x;
    Mat half_pow = MatPower(x, y/2);
    Mat ret = half_pow * half_pow;
    if(y%2==1)
        ret = ret * x;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll N, M;
    cin >> N >> M;

    Mat mat(M);
    mat[0][0] = 1;
    mat[0][M-1] = 1;
    for(int row = 1;row<M;row++)
        mat[row][row-1] = 1;

    Mat ret = MatPower(mat,N);
    ll answer = 0;
    for(int col = 0;col<M;col++)
        answer += ret[M-1][col];

    cout<<answer% DIV<<endl;

    return 0;
}