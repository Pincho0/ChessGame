#pragma once
#include <vector>

class Bishop {
public:
    int x;
    int y;
    bool white;

    Bishop(int x, int y, bool white);

    void getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& possibleMoves);
};

