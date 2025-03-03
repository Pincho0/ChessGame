#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include "chessBoard.hpp"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int TILE_SIZE = SCREEN_WIDTH / 8; // Taille d'une case

// Fonction pour charger une texture
SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

// Fonction pour dessiner une pi�ce
void drawPiece(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

// Fonction pour dessiner l'�chiquier
void drawChessboard(SDL_Renderer* renderer);

// Fonction pour cr�er la fen�tre SDL
SDL_Window* create_Window();

// Fonction pour cr�er le renderer SDL
SDL_Renderer* create_Renderer(SDL_Window* window);

// Fonction principale du jeu
void run();


