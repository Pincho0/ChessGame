#pragma once
#include <vector>
class Queen {
public:
    int x;
    int y;
    bool white;

    Queen(int x, int y, bool white);

    void getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& moves);
};


