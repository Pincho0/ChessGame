#include "chessBoard.hpp"

	

ChessBoard::ChessBoard(){
	initBoard();
}

int(&ChessBoard::getState())[8][8]{ return state; }

void ChessBoard::displayBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << state[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
void ChessBoard::initBoard() {
	// Pion:6, Tour:5, Cavalier:4, Fou:3, Reine:2, Roi:1
	//Blanc: Nombre positif, Noir: Nombre négatif
	//Case vide: 0
	int initialPos[8] = { 5,4,3,2,1,3,4,5 };
	for (int k = 0; k < 8; k++) {
		state[1][k] = 6;
		state[0][k] = initialPos[k];
	}

	for (int k = 0; k < 8; k++) {
		state[6][k] = -6;
		state[7][k] = -initialPos[k];
	}
}

void ChessBoard::makeAMove(int old_x, int old_y, int new_x, int new_y) {
	state[new_x][new_y] = state[old_x][old_y];
	state[old_x][old_y] = 0;
}

std::vector<std::pair<int, int>> ChessBoard::getAttackedSquares(bool isWhite) {
    std::vector<std::pair<int, int>> attackedSquares;

    // Parcours du plateau pour analyser les pièces adverses
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int piece = state[i][j];

            // Vérifier si la pièce appartient à l'adversaire
            if ((isWhite && piece < 0) || (!isWhite && piece > 0)) {
                // Si c'est une pièce adverse, on récupère les cases qu'elle attaque
                switch (piece) {
                case 6: // Pion
                case -6: {
                    Pawn pawn(i, j, (piece > 0));
                    pawn.getAttackedSquares(state, attackedSquares);
                    
                    break;
                }
                case 3: // Fou
                case -3: {
                    Bishop bishop(i, j, (piece > 0));
                    bishop.getPossibleMoves(state, attackedSquares);
                    break;
                }
                case 5: // Tour
                case -5: {
                    Rook rook(i, j, (piece > 0));
                    rook.getPossibleMoves(state, attackedSquares);
                    break;
                }
                case 2: // Reine
                case -2: {
                    Queen queen(i, j, (piece > 0));
                    queen.getPossibleMoves(state, attackedSquares);
                    break;
                }
                case 4: // Cavalier
                case -4: {
                    Knight knight(i, j, (piece > 0));
                    knight.getPossibleMoves(state, attackedSquares);
                    break;
                }
                case 1: // Roi
                case -1: {
                    King king(i, j, (piece > 0));
                    king.getPossibleMoves(state, attackedSquares);
                    break;
                }
                }
            }
        }




        
    }
    return attackedSquares;
}

bool ChessBoard::isKingInCheck(bool isWhite) {
	// Trouver la position du roi adverse
    std::pair<int, int> kingPosition;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int piece = state[i][j];
            if ((isWhite && piece == 1) || (!isWhite && piece == -1)) {
                // Le roi est trouvé
                kingPosition = { i, j };
                break;
            }
        }
    }

    // Obtenir les cases attaquées par l'adversaire
    std::vector<std::pair<int, int>> attackedSquares = getAttackedSquares(isWhite);
    

    // Vérifier si la case du roi est attaquée
    for (const auto& square : attackedSquares) {
        if (square.first == kingPosition.first && square.second == kingPosition.second) {
            return true; // Le roi est en échec
        }
    }

    return false; // Le roi n'est pas en échec
}


