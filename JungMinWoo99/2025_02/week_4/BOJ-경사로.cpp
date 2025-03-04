#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#define endl '\n'

#include <queue>

using namespace std;

class SlideQue
{
public:
    SlideQue(int slide_size) : slide_size(slide_size), size(0) {}
    void pop() { size--; }
    void push(int i)
    {
        back = i;
        size++;
        if(size > slide_size)
            size = slide_size;
    }
    int getSize() { return size; }
    int getBack() { return back; }
    void clear() { size = 0; }

private:
    int slide_size;
    int back;
    int size;
};

class Grid
{
public:
    Grid(int road_len, int ramp_len) : N(road_len), L(ramp_len), rows(road_len), cols(road_len)
    {
        for (int i = 0; i < road_len; i++)
        {
            for (int l = 0; l < road_len; l++)
            {
                int input;
                cin >> input;
                rows[i].push_back(input);
                cols[l].push_back(input);
            }
        }
    }

    int getAnswer()
    {
        int ret = 0;
        for(int i = 0;i<N;i++)
            if(canWalk(rows[i]))
                ret++;
        for(int i = 0;i<N;i++)
            if(canWalk(cols[i]))
                ret++;
        return ret;
    }

private:
    int N, L;
    vector<vector<int>> rows;
    vector<vector<int>> cols;

    bool canWalk(const vector<int> &road)
    {
        bool ret = true;
        SlideQue slide_que(L);
        slide_que.push(road[0]);
        for (int i = 1; i < N; i++)
        {
            int prev_block = slide_que.getBack();
            if (prev_block == road[i])
            {
                slide_que.push(road[i]);
            }
            else if(prev_block + 1 == road[i])
            {
                if(slide_que.getSize() == L)
                {
                    slide_que.clear();
                    slide_que.push(road[i]);
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            else if(prev_block - 1 == road[i])
            {
                slide_que.clear();
                slide_que.push(road[i]);
                while(slide_que.getSize() != L)
                {
                    i++;
                    if(i==N||slide_que.getBack() != road[i])
                    {
                        ret = false;
                        break;
                    }

                    slide_que.push(road[i]);
                }
                if(!ret)
                    break;
                else
                    slide_que.clear();
            }
            else
            {
                ret = false;
                break;
            }
        }

        return ret;
    }
};

int main()
{
    int N, L;
    cin>> N>>L;
    Grid grid(N,L);
    cout<<grid.getAnswer();
}