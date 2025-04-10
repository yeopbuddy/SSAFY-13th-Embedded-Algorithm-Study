#include <iostream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

int r, c, m;
map<int, tuple<int, int, int, int, int>> SharkInfo; // id -> (x, y, v, d, s)

void SharkMoveUp(int& cx, int cv, int& cd) {
    int cr = r - 1;
    bool isReversed = false;
    if (cx >= cv) {
        cx -= cv;
    } else {
        cv -= cx;
        cx = 0;
        isReversed = !isReversed;
        while (cv != 0) {
            if (cv >= cr) { // 현재 상/하 길이보다 상어가 움직일 수 있는 남은 거리수가 더 많을 때
                cv -= cr; // 그만큼 빼주고
                cx = isReversed ? cr : 0; // 아래 방향 향하고 있었으면 맨 아래로 cx값 옮겨주기, 위 방향 향하고 있었으면 맨 위로 cx 값 옮겨주기
            } else { // 현재 상/하 길이보다 상어가 움직일 수 있는 남은 거리수가 더 적으면
                cx = isReversed ? cv : cr - cv; // 아래 방향 향하고 있었으면 상어 남은 거리로 cx 값 옮겨주기, 위 방향 향하고 있었으면 cr-상어 남은 거리로 cx 값 옮겨주기
                cv = 0;
            }
            if (cv != 0) isReversed = !isReversed;
        }
    }
    if (isReversed) cd = 2; // 뒤집힌 채로 끝나면 상어 방향 아래로 최신화
}

void SharkMoveDown(int& cx, int cv, int& cd) {
    int cr = r - 1;
    if (cr - cx >= cv) { // 아래로 남은 만큼 이동하고 끝날 수 있으면
        cx += cv; // 아래로 옮겨주고 땡
    } else {
        cv -= (cr - cx); // 아니면 아래로 옮기고, 위로 가는 것은 구현해둔 함수 사용
        cx = cr;
        cd = 1;
        SharkMoveUp(cx, cv, cd);
    }
}

void SharkMoveLeft(int& cy, int cv, int& cd) { // 위, 아래와 동일하게 왼쪽 구현하고, 오른쪽에서는 왼쪽 구현한거 사용
    int cc = c - 1;
    bool isReversed = false;
    if (cy >= cv) {
        cy -= cv;
    } else {
        cv -= cy;
        cy = 0;
        isReversed = !isReversed;
        while (cv != 0) {
            if (cv >= cc) {
                cv -= cc;
                cy = isReversed ? cc : 0;
            } else {
                cy = isReversed ? cv : cc - cv;
                cv = 0;
            }
            if (cv != 0) isReversed = !isReversed;
        }
    }
    if (isReversed) cd = 3;
}

void SharkMoveRight(int& cy, int cv, int& cd) {
    int cc = c - 1;
    if (cc - cy >= cv) {
        cy += cv;
    } else {
        cv -= (cc - cy);
        cy = cc;
        cd = 4;
        SharkMoveLeft(cy, cv, cd);
    }
}

void moveSharks() {
    map<pair<int, int>, tuple<int, int, int, int>> newPos; // (x,y) -> (v,d,s,id)

    for (auto& [id, info] : SharkInfo) {
        auto [x, y, v, d, s] = info;

        switch (d) { // 방향에 따라 상어 움직여주기
            case 1: SharkMoveUp(x, v, d); break;
            case 2: SharkMoveDown(x, v, d); break;
            case 3: SharkMoveRight(y, v, d); break;
            case 4: SharkMoveLeft(y, v, d); break;
        }

        pair<int, int> pos = {x, y};
        if (!newPos.count(pos) || get<2>(newPos[pos]) < s) { // 해당 좌표에 상어가 안 들어왔거나, 그 좌표에 있는 상어보다 크기가 크면
            newPos[pos] = make_tuple(v, d, s, id); // 저장해줌
        }
    }

    SharkInfo.clear(); // 비우고
    for (auto& [pos, data] : newPos) { // 최신화
        auto [v, d, s, id] = data;
        SharkInfo[id] = {pos.first, pos.second, v, d, s};
    }
}

int main() {
    cin >> r >> c >> m;
    for (int i = 0; i < m; ++i) {
        int rs, cs, vs, ds, ss;
        cin >> rs >> cs >> vs >> ds >> ss;
        SharkInfo[i] = {rs - 1, cs - 1, vs, ds, ss};
    }

    int ANS = 0;
    for (int fisher = 0; fisher < c; ++fisher) {
        int catchId = -1, minX = r;
        for (auto& [id, info] : SharkInfo) {
            int x = get<0>(info);
            int y = get<1>(info);
            if (y == fisher && x < minX) {
                minX = x;
                catchId = id;
            }
        }
        if (catchId != -1) { // 뭐라도 잡은 경우
            ANS += get<4>(SharkInfo[catchId]);
            SharkInfo.erase(catchId);
        }
        moveSharks(); // 이동
    }
    cout << ANS;
    return 0;
}