#include "knight.hpp"

Knight::Knight(int x, int y, bool white) : x(x), y(y), white(white) {}



void Knight::getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& moves) {
    // Liste des 8 mouvements possibles d'un cavalier
    int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };

    for (auto& move : knightMoves) {
        int newX = x + move[0];
        int newY = y + move[1];

        // Vérifier si la case est dans les limites du plateau
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            int target = state[newX][newY];

            // Ajouter la case si elle est vide ou contient une pièce ennemie
            if (target == 0 || (white && target < 0) || (!white && target > 0)) {
                moves.push_back({ newX, newY });
            }
        }
    }
}