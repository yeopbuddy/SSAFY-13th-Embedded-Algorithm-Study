#include<iostream>
using namespace std;

int scoreDP[301] = {};    // index : n , value : n개 계단까지 오는 경로 중 최댓값
int stairs[301] = {};    // 각 계단마다 점수

int StairsUp(int n) {
   scoreDP[1] = stairs[1];
   scoreDP[2] = stairs[1] + stairs[2];
   scoreDP[3] = max(stairs[1], stairs[2]) + stairs[3];

   for (int i = 4; i <= n; i++)
   {
      // 두 단계 이전에서 선택하거나
      // 세 단계 이전 + 직전 계단에서 선택하거나
      scoreDP[i] = max(scoreDP[i - 2], scoreDP[i - 3] + stairs[i - 1]) + stairs[i];
   }
   return scoreDP[n];
}
int main() {
   int stairsCnt;
   cin >> stairsCnt;

   for (int i = 1; i <= stairsCnt; i++)
   {
      cin >> stairs[i]; // index가 곧 계단 번째 
   }
   cout << StairsUp(stairsCnt);
}