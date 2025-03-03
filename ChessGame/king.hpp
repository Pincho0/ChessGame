#pragma once
#include <vector>
class King {
public:
    int x;
    int y;
    bool white;

    King(int x, int y, bool white);

    void getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& moves);
};


