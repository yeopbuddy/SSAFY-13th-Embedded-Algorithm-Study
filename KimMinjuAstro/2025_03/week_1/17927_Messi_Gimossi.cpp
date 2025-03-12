/*
N을 아는게 이 문제의 키라고 생각함
1. M번째 글자를 포함하고 있는 N을 찾는다. : FindLength
2. N을 찾았다면 해당 문자열의 M번째 글자를 찾는다 : FindChar
*/
#include<iostream>
using namespace std;
long long len[100];
int N = 1;
int M;

long long FindLength(int n) {
   if (n == 1)return 5;
   if (n == 2)return 13;
   if (len[n] != 0)return len[n];
   return len[n] = FindLength(n - 1) + FindLength(n - 2) + 1;  // 공백 한 글자도 넣어주기
}

char FindChar(int n, long long M) {
   if (n == 1)return "Messi"[M - 1];
   if (n == 2)return "Messi Gimossi"[M - 1];

   long long len = FindLength(n - 1);
   if (M <= len) {
      return FindChar(n - 1, M);
   }
   else if (M == len + 1) {
      return ' ';
   }
   else {
      return FindChar(n - 2, M - len - 1);
   }
}

int main() {
   cin >> M;

   while (FindLength(N) < M)N++;

   char result = FindChar(N, M);

   if (result == ' ') {
      cout << "Messi Messi Gimossi";
   }
   else {
      cout << result;
   }

   return 0;
}