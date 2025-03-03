#include "loop.hpp"


SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
      

    if (!texture) {
        SDL_Log("Erreur de création de la texture : %s", SDL_GetError());
    }
    return texture;
}

// Fonction pour dessiner une pièce
void drawPiece(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_FRect destRect = { x* TILE_SIZE, y* TILE_SIZE, TILE_SIZE, TILE_SIZE }; // Taille de la case
    SDL_RenderTexture(renderer, texture, NULL, &destRect);
}

void renderBoard(SDL_Renderer* renderer, ChessBoard& chessBoard, SDL_Texture* textures[12], std::vector<std::pair<int, int>> highlightSquare) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int(&boardState)[8][8] = chessBoard.getState();

    //Dessiner l'échiquier (cases noires et blanches)
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 74, 115, 153, 255); // Case claire
            }
            else {
                SDL_SetRenderDrawColor(renderer, 245, 230, 204, 255); // Case foncée
            }

            SDL_FRect rect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //Colorier les cases spéciales (cases en jaune pour les mouvements possibles et la sélection)
    for (const auto& square : highlightSquare) {
        int squareRow = square.first;
        int squareCol = square.second;
        SDL_SetRenderDrawColor(renderer, 240, 220, 100, 255); // Jaune pour les mouvements possibles
        SDL_FRect rect = { squareCol * TILE_SIZE, squareRow * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    //Dessiner les pièces PAR-DESSUS les cases colorées
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int piece = boardState[row][col];
            if (piece != 0) {
                int textureIndex = (piece > 0) ? (piece - 1) : (-piece + 5);
                drawPiece(renderer, textures[textureIndex], col, row);
            }
        }
    }

    SDL_RenderPresent(renderer);
}



SDL_Window* create_Window() {
	SDL_Window* window = SDL_CreateWindow("Echiquier SDL", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) {
		SDL_Log("Erreur de création de la fenêtre : %s", SDL_GetError());
		SDL_Quit();
	}
    return window;
}

SDL_Renderer* create_Renderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        SDL_Log("Erreur de création du renderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();

    }
	return renderer;
}


void run() {
    // Initialisation de SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur d'initialisation de SDL : %s", SDL_GetError());

    }

	SDL_Window* window = create_Window();
	SDL_Renderer* renderer = create_Renderer(window);

    // Charger les textures pour chaque pièce
    SDL_Texture* textures[12];  // 6 pièces pour chaque couleur (blanc et noir)
    textures[0] = loadTexture("image piece/white-king.png", renderer);
    textures[1] = loadTexture("image piece/white-queen.png", renderer);
    textures[2] = loadTexture("image piece/white-bishop.png", renderer);
    textures[3] = loadTexture("image piece/white-knight.png", renderer);
    textures[4] = loadTexture("image piece/white-rook.png", renderer);
    textures[5] = loadTexture("image piece/white-pawn.png", renderer);
    textures[6] = loadTexture("image piece/black-king.png", renderer);
    textures[7] = loadTexture("image piece/black-queen.png", renderer);
    textures[8] = loadTexture("image piece/black-bishop.png", renderer);
    textures[9] = loadTexture("image piece/black-knight.png", renderer);
    textures[10] = loadTexture("image piece/black-rook.png", renderer);
    textures[11] = loadTexture("image piece/black-pawn.png", renderer);

	ChessBoard chessBoard;
	
    bool running = true;
    SDL_Event event;
    bool isWhiteTurn = true;
    int selectedRow = -1, selectedCol = -1;
    std::vector<std::pair<int, int>> possibleMoves;
    while (running) {
        SDL_WaitEvent(&event);
        int(&boardState)[8][8] = chessBoard.getState();
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN: 
            if (event.motion.x >= 0)  
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                int col = mouseX / TILE_SIZE;
                int row = mouseY / TILE_SIZE; bool validMove = false;
                for (const auto& move : possibleMoves) {
                    if (move.first == row && move.second == col) {
                        validMove = true;
                        break;
                    }
                }

                if (validMove) {
                    // Déplacer la pièce
                    chessBoard.makeAMove(selectedRow, selectedCol, row, col);
                    // Vérifier si le roi est en echec après le mouvement
                    if (chessBoard.isKingInCheck(isWhiteTurn)) {
                        std::cout << "Le roi est en echec" << std::endl;

                        // Annuler le mouvement si le roi est en échec
                        chessBoard.makeAMove(row, col, selectedRow, selectedCol);
                    }
                    else {
                        // Réinitialiser la sélection
                        selectedRow = -1;
                        selectedCol = -1;
                        possibleMoves.clear();
                        isWhiteTurn = !isWhiteTurn;  // Passer au tour de l'adversaire
                    }
                }
                else if (boardState[row][col] != 0) {
                    // Nouvelle sélection d'une pièce
                    int selectedPiece = boardState[row][col];
                    

                    
                    if ((isWhiteTurn && selectedPiece > 0) || (!isWhiteTurn && selectedPiece < 0)) {
                        selectedRow = row;
                        selectedCol = col;
                        possibleMoves.clear(); // Vider l'ancienne liste
                        switch (selectedPiece) {
                        case 6:
                        case -6: {
                            Pawn pawn(selectedRow, selectedCol, (selectedPiece > 0));
                            pawn.getPossibleMoves(boardState, possibleMoves);
                            break;
                        }

                        case 3:
                        case -3: {
                            Bishop bishop(selectedRow, selectedCol, (selectedPiece > 0));
                            bishop.getPossibleMoves(boardState, possibleMoves);
                            break;
                        }

                        case 5:
                        case -5: {
                            Rook rook(selectedRow, selectedCol, (selectedPiece > 0));
                            rook.getPossibleMoves(boardState, possibleMoves);
                            break;
                        }
                        case 2:
                        case -2: {
                            Queen queen(selectedRow, selectedCol, (selectedPiece > 0));
                            queen.getPossibleMoves(boardState, possibleMoves);
                            break;
                        }
                        case 4:
                        case -4: {
                            Knight knight(selectedRow, selectedCol, (selectedPiece > 0));
                            knight.getPossibleMoves(boardState, possibleMoves);
                            break;
                        }
                        case 1:
                        case -1: {
                            King king(selectedRow, selectedCol, (selectedPiece > 0));
                            king.getPossibleMoves(boardState, possibleMoves);
                            break;
                        }
                        default:
                            break;
                        }
                    }
                }
                else {
                    // Clic sur une case vide hors d'un mouvement possible -> désélectionner
                    selectedRow = -1;
                    selectedCol = -1;
                    possibleMoves.clear();
                }
                break;
            }
        }
        std::vector<std::pair<int, int>> squareToHighLight = possibleMoves;
        squareToHighLight.push_back({ selectedRow, selectedCol });
        renderBoard(renderer, chessBoard, textures, squareToHighLight);
    }


    // Libérer les ressources
    for (int i = 0; i < 12; i++) {
        SDL_DestroyTexture(textures[i]);
    }

    SDL_RenderPresent(renderer); // Afficher le rendu



}

    
    

