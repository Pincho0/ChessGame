#include "pawn.hpp"
#include <iostream>

Pawn::Pawn(int x, int y, bool white) : x(x), y(y), white(white) {}



void Pawn::getPossibleMoves(int(&state)[8][8], std::vector<std::pair<int, int>>& possibleMoves) {
    int direction = white ? 1 : -1; // 1 pour blanc, -1 pour noir
    int startRow = white ? 1 : 6;   // Ligne de départ des pions blancs et noirs

    // Vérifier la case devant (si elle est vide)
    if (x + direction >= 0 && x + direction < 8 && state[x + direction][y] == 0) {
        possibleMoves.push_back({ x + direction, y });

        // Si le pion est sur sa case initiale et que la case à deux cases devant est libre
        if (x == startRow && state[x + 2 * direction][y] == 0) {
            possibleMoves.push_back({ x + 2 * direction, y });
        }
    }

    // Vérifier la capture diagonale gauche
    if (y - 1 >= 0 && x + direction >= 0 && x + direction < 8) {
        if (white && state[x + direction][y - 1] < 0) {  // Capturer une pièce noire
            possibleMoves.push_back({ x + direction, y - 1 });
        }
        if (!white && state[x + direction][y - 1] > 0) { // Capturer une pièce blanche
            possibleMoves.push_back({ x + direction, y - 1 });
        }
    }

    // Vérifier la capture diagonale droite
    if (y + 1 < 8 && x + direction >= 0 && x + direction < 8) {
        if (white && state[x + direction][y + 1] < 0) {  // Capturer une pièce noire
            possibleMoves.push_back({ x + direction, y + 1 });
        }
        if (!white && state[x + direction][y + 1] > 0) { // Capturer une pièce blanche
            possibleMoves.push_back({ x + direction, y + 1 });
        }
    }
}

void Pawn::getAttackedSquares(int(&state)[8][8], std::vector<std::pair<int, int>>& attackedSquares) {
    int direction = white ? 1 : -1;  // Direction dépend de la couleur du pion

    // Vérifier la capture diagonale gauche
    if (y - 1 >= 0 && x + direction >= 0 && x + direction < 8) {
        if (white) { 
            attackedSquares.push_back({ x + direction, y - 1 });
        }
        if (!white) { 
            attackedSquares.push_back({ x + direction, y - 1 });
        }
    }

    // Vérifier la capture diagonale droite
    if (y + 1 < 8 && x + direction >= 0 && x + direction < 8) {
        if (white) {  
            attackedSquares.push_back({ x + direction, y + 1 });
        }
        if (!white) { 
            attackedSquares.push_back({ x + direction, y + 1 });
        }
    }
}



