#include "bishop.hpp"

    

Bishop::Bishop(int x, int y, bool white) : x(x), y(y), white(white) {}


void Bishop::getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& possibleMoves) {
    int directions[4][2] = {
        {1, 1},   // Bas-Droite
        {1, -1},  // Bas-Gauche
        {-1, 1},  // Haut-Droite
        {-1, -1}  // Haut-Gauche
    };

    for (int d = 0; d < 4; ++d) {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int newX = x + dx;
        int newY = y + dy;

        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            if (state[newX][newY] == 0) {
                possibleMoves.push_back({ newX, newY });
            }
            else {
                // Vérifie si l'on peut capturer une pièce adverse
                if ((white && state[newX][newY] < 0) || (!white && state[newX][newY] > 0)) {
                    possibleMoves.push_back({ newX, newY });
                }
                break; // Arrêter car une pièce bloque le passage
            }
            newX += dx;
            newY += dy;
        }
    }
}

