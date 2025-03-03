#pragma once
#include <vector>
class Pawn {
public:
    int x;
    int y;
    bool white;

    Pawn(int x, int y, bool white);

    void getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& possibleMoves);

	void getAttackedSquares(int(&state)[8][8], std::vector<std::pair<int, int>>& attackedSquares);
};


