///*
//n의 짝수 제곱들만 뽑아서 경우의 수를 구하자
//*/
//
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<cmath>
//
//using namespace std;
//long long n;    // 체크해야할 범위
//int k;            // k진법
//int digit;        // n까지 도달하는데 필요한 자릿수
//int digitArr[1000];// digit-1 까지가 진법변환수
//int cases;
//int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(NULL);
//
//   cin >> n >> k;
//
//   // digit 계산, digitArr에 k진법으로 변환한 수 넣기
//   while (1) {
//      if (n / k > 0) {
//         digitArr[digit] = n % k;
//         digit++;
//         n /= k;
//      }
//      else {
//         digitArr[digit] = n;
//         digit++;
//         break;
//      }
//   }
//   // 계산하기 쉽게 역순으로 정렬
//   reverse(digitArr, digitArr + digit);
//
//   // n보다 작거나 같은 최댓값으로 변경
//   bool isChanging = false;
//   if (digit % 2 == 1) {
//      for (int i = 0; i < digit; i++)
//      {
//         if (isChanging && (i % 2 == 0)) {
//            digitArr[i] = k - 1;
//         }
//         if (i % 2 == 1) {
//            if (digitArr[i] > 0) {
//               digitArr[i] = 0;
//               isChanging = true;
//            }
//         }
//      }
//   }
//   else {
//      for (int i = 0; i < digit; i++)
//      {
//         if (isChanging && (i % 2 == 1)) {
//            digitArr[i] = k - 1;
//         }
//         if (i % 2 == 0) {
//            if (digitArr[i] > 0) {
//               digitArr[i] = 0;
//               isChanging = true;
//            }
//         }
//      }
//   }
//
//
//   int power = (digit % 2 == 0) ? digit / 2 - 1 : digit / 2;
//   if (digit % 2 == 1) {
//      for (int i = 0; i < digit; i++) {
//         if (i % 2 == 0) {
//            cases += digitArr[i] * (int)(pow(k, power));
//            power--;
//         }
//      }
//   }
//   else {
//      for (int i = 0; i < digit; i++) {
//         if (i % 2 == 1) {
//            cases += digitArr[i] * (int)(pow(k, power));
//            power--;
//         }
//      }
//   }
//
//
//   cout << int(cases + 1);
//   return 0;
//}