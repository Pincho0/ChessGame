#include "king.hpp"

King::King(int x, int y, bool white) : x(x), y(y), white(white) {}

    

void King::getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& moves) {
    // Déplacements possibles du roi (8 directions)
    int kingMoves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (auto& move : kingMoves) {
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