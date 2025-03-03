#pragma once
#include <iostream>
#include <vector>
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"

class ChessBoard {
private:
    int state[8][8] = { 0 };

public:
    ChessBoard();

    int(&getState())[8][8];

    void displayBoard();

    void initBoard();

	void makeAMove(int old_x, int old_y, int new_x, int new_y);

    std::vector<std::pair<int, int>> getAttackedSquares(bool isWhite);

    bool isKingInCheck(bool isWhite);
};


