#include "rook.hpp"



Rook::Rook(int x, int y, bool white) : x(x), y(y), white(white) {}

    

void Rook::getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& possibleMoves) {
    // Directions possibles : haut, bas, gauche, droite
    int directions[4][2] = {
        {-1, 0}, {1, 0},  // Haut, Bas
        {0, -1}, {0, 1}   // Gauche, Droite
    };

    for (auto& dir : directions) {
        int newX = x, newY = y;
        while (true) {
            newX += dir[0];
            newY += dir[1];

            // Vérifier si on reste dans l'échiquier
            if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) break;

            int piece = state[newX][newY];

            if (piece == 0) {
                // Case vide, on peut avancer
                possibleMoves.push_back({ newX, newY });
            }
            else {
                // Il y a une pièce, vérifier si on peut capturer
                if ((white && piece < 0) || (!white && piece > 0)) {
                    possibleMoves.push_back({ newX, newY });
                }
                break; // On ne peut pas sauter par-dessus une pièce
            }
        }
    }
}
