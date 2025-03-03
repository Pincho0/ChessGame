#pragma once
#include <vector>
class Knight {
public:
    int x;
    int y;
    bool white;

    Knight(int x, int y, bool white);

    void getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& moves);
};

