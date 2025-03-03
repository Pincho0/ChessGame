#pragma once
#include <vector>
class Rook {
public:
    int x;
    int y;
    bool white;

    Rook(int x, int y, bool white);

	void getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& possibleMoves);
};


