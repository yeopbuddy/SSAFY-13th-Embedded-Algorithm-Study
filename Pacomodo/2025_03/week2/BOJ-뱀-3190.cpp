// 3190번 뱀
// 구현, 시뮬레이션
/*
접근 방법: 
충돌 판정은 unordered_set으로 구현. 
꼬리 칸 비우기는 덱으로 구현.
주의할 점은 pair<int, int>에 해당하는 해시함수가 없기 때문에 직접 해시함수를 구현해야함.
해시함수는 GPT에게 맡김.

해시함수에 대한 보충 설명:
- std::hash<type>란?
C++의 functional 헤더에 정의된 해시 함수 객체로, 특정 타입에 대한 해시값을 계산하는데에 사용. 

template <typename T>
struct hash;

이렇게 템플릿으로 정의되어 있으며, 다음과 같은 기본 타입들에 대해 std::hash가 제공됨.
int, float, double, std::string, char, bool, T*(포인터 타입), std::nullptr_t

사용 예시:
#include <iostream>
#include <functional>  // std::hash

int main() {
    std::hash<int> hash_fn;  // std::hash<int>의 인스턴스 생성
    int x = 42;
    std::size_t hash_value = hash_fn(x);  // x의 해시값 계산

    std::cout << "Hash of " << x << " is " << hash_value << std::endl;
    return 0;
}

- 그러면 hash<int>{}()처럼 사용하는 이유는? 
C++에서는 람다식처럼 생성자를 호출할 때 {}를 사용 가능합니다.
즉, size_t h1 = hash<int>{}(p.first);
이 코드는 std::hash<int>객체를 생성한 후 ()를 붙여 바로 operator()를 호출하는 형태가 됩니다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional>
using namespace std;
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

// 아래의 해시 함수는 GPT에게 맡겼습니다. 아주 강력한 해시함수라네요.
struct pair_hash {
    size_t operator()(const pair<int, int>& p) const {
        size_t h1 = hash<int>{}(p.first);
        size_t h2 = hash<int>{}(p.second);
        // Fibonacci Hashing + Bit Mixing
        return h1 ^ (h2 * 0x9e3779b97f4a7c15ULL);
    }
};

pair<int, int> stretch(pair<int, int> head, int nowDir){
    if (nowDir == 0) return {head.first, head.second+1};
    if (nowDir == 2) return {head.first, head.second-1};
    if (nowDir == 1) return {head.first+1, head.second};
    if (nowDir == 3) return {head.first-1, head.second};
    return {-1,-1};
}

bool checkCollide(const unordered_set<pair<int, int>, pair_hash>& body, const int& N, pair<int, int> head){
    if (body.find(head) != body.end()) return true;
    if (head.first < 1 || head.first > N || head.second < 1 || head.second > N) return true;
    return false;
}

int main(void){
    fastio;
    size_t N; cin >> N; // 보드의 크기
    size_t K; cin >> K; // 사과의 개수
    unordered_set<pair<int, int>, pair_hash> apple;
    pair<int, int> a;
    for (size_t i = 0; i < K; ++i){
        cin >> a.first >> a.second;
        apple.insert(a);
    }
    size_t L; cin >> L; // 방향 전환의 개수
    vector<pair<int, char>> query(L);
    for (size_t i = 0; i < L; ++i){
        cin >> query[i].first >> query[i].second; 
    }
    pair<int, int> head = {1, 1};
    unordered_set<pair<int, int>, pair_hash> snakeBody;
    deque<pair<int, int>> snake;
    snakeBody.insert(head);
    snake.push_back(head);
    int time = 1;
    size_t idx = 0; // idx: 방향전환 쿼리의 인덱스.
    int nowDir = 0; //0: 오른쪽, 1: 아래, 2: 왼쪽, 3: 위.
    // 이렇게 시계방항 순으로 설정하면, D를 받으면 +1, L을 받으면 -1을 해주면 됩니다.
    while (true){
        // 1. 먼저 뱀은 몸 길이를 now_dir 방향으로 한 칸 늘립니다.
        pair<int, int> newHead = stretch(head, nowDir);
        if (checkCollide(snakeBody, N, newHead)){
            cout << time;
            return 0;
        }
        // 2. 만약 이동한 칸에 사과가 있다면 그 칸에 있던 사과가 없어집니다.
        if (apple.find(newHead) != apple.end()){
            apple.erase(newHead);
            snakeBody.insert(newHead);
            snake.push_back(newHead);
            head = newHead;
        }
        else {
            snake.push_back(newHead);
            snakeBody.insert(newHead);
            snakeBody.erase(snake.front());
            snake.pop_front();
            head = newHead;
        }
        // 3. 만약 방향 전환 쿼리와 일치한다면 방향 전환을 해줍니다.
        if (idx == L){
            ++time;
            continue;
        }
        if (time == query[idx].first){
            if (query[idx].second == 'D') ++nowDir;
            else --nowDir;
            if (nowDir < 0) nowDir += 4;
            if (nowDir > 3) nowDir -= 4;
            ++idx;
        }
        ++time;
    }
}