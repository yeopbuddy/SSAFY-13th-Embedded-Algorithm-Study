#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

int BinSearch(vector<int> &input, int target)
{
    int start = 0;
    int end = input.size();
    int mid = (start + end) / 2;
    while (start != mid)
    {
        if (target == input[mid])
            break;
        else if (target < input[mid])
            end = mid;
        else
            start = mid;
        mid = (start + end) / 2;
    }

    if (target == input[mid])
    {
        start = mid;
        while (start - 1 > -1 && input[start - 1] == target)
            start--;
        end = mid;
        while (end + 1 < input.size() && input[end + 1] == target)
            end++;

        return end - start + 1;
    }
    else
        return 0;
}

int main(void)
{
    int N, M;
    cin >> N >> M;
    vector<int> arr;

    for (int i = 0; i < N; i++)
    {
        bitset<30> input;
        cin >> input;

        arr.push_back(input.to_ulong());
    }

    sort(arr.begin(), arr.end());

    int answer = 0;

    // 모두 같은 경우
    for (int i = 0; i < arr.size(); i++)
    {
        answer += (BinSearch(arr, arr[i]) - 1);
    }

    // 하나만 다른 경우
    for (int i = 0; i < arr.size(); i++)
    {
        bitset<30> next(arr[i]);
        for (int i = 0; i < M; i++)
        {
            int target = next.flip(i).to_ulong();
            answer += BinSearch(arr, target);
            next.flip(i);
        }
    }

    // 두개만 다른 경우
    for (int i = 0; i < arr.size(); i++)
    {
        bitset<30> next(arr[i]);
        for (int i = 0; i < M; i++)
        {
            bitset<30> target1 = next.flip(i);
            for (int l = i + 1; l < M; l++)
            {
                int target2 = target1.flip(l).to_ulong();
                answer += BinSearch(arr, target2);
                target1.flip(l);
            }
            next.flip(i);;
        }
    }

    cout << answer / 2 << endl;
}