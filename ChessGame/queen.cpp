#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
Queen::Queen(int x, int y, bool white) : x(x), y(y), white(white) {}

   

void Queen::getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& moves) {
    // Simuler les mouvements de la tour
    Rook rook(x, y, white);
    rook.getPossibleMoves(state, moves);

    // Simuler les mouvements du fou
    Bishop bishop(x, y, white);
    bishop.getPossibleMoves(state, moves);
}
