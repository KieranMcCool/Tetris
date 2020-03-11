/* This Header defines all the data structures and method for the core game logic. */
#ifndef GAME_H

#define GAME_H

#include <stdbool.h>
#include <SDL.h>

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

typedef enum piece { I, O, T, S, Z, J, L } Piece;

typedef struct grid {
    Piece cells[GRID_HEIGHT * GRID_WIDTH];
} Grid;

Grid Grid_Init();
SDL_Point Grid_IndexToCoords(int n);
int Grid_CoordsToIndex(SDL_Point p);
Piece Grid_PieceAtIndex(int n);
Piece Grid_PieceAtCoords(SDL_Point p);

typedef struct gameState {
    Grid *grid;
    int score;
    bool dropping;
    bool playing;
} GameState;

GameState *GameState_Init();
bool GameState_Tick();

#endif 