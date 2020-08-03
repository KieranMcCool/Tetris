/* This Header defines all the data structures and method for the core game logic. */
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL.h>
#include <string.h>
#include "input.h"

#define MAX_PIECE_HEIGHT 3

#define GRID_WIDTH 10
#define GRID_HEIGHT 23

typedef enum piece { I, O, T, S, Z, J, L, Empty } Piece;

typedef struct grid {
    Piece cells[GRID_HEIGHT * GRID_HEIGHT];
    bool cellsActiveState[GRID_HEIGHT * GRID_WIDTH];
} Grid;

Grid *Grid_Init();
SDL_Point Grid_IndexToCoords(int n);
int Grid_CoordsToIndex(SDL_Point p);
Piece Grid_PieceAtIndex(Grid *grid, int n);
Piece Grid_PieceAtCoords(Grid *grid, SDL_Point p);
void Grid_SpawnPiece(Grid *grid);
bool Grid_IndexIsActive(Grid *grid, int i);
bool Grid_CoordIsActive(Grid *grid, SDL_Point p);
void Grid_ClearActiveStates(Grid *grid);

typedef struct gameState {
    Grid *grid;
    int score;
    bool dropping;
    int droppedBlocks;
    bool playing;
    uint32_t tick;
    int gameSpeed;
} GameState;

GameState *GameState_Init();
void GameState_Tick(GameState *gameState);
void GameState_ClearLines(GameState *gameState);
bool GameState_Gravity(GameState *gameState);
void GameState_NextPiece(GameState *gameState);
void GameState_CheckLoss(GameState *gameState);
bool GameState_BoardIsClear(GameState *gameState);
void GameState_ProcessInput(Action action, GameState *gameState);
void GameState_MovePiece(Action action, GameState *gameState);

static char IPiece[] = 
"1000\
1000\
1000\
1000";

static char OPiece[] = 
"0000\
0000\
1100\
1100";

static char TPiece[] = 
"0000\
0000\
0100\
1110";

static char SPiece[] = 
"0000\
0000\
0110\
1100";

static char ZPiece[] = 
"0000\
0000\
1100\
0110";

static char JPiece[] = 
"0000\
0100\
0100\
1100";

static char LPiece[] = 
"0000\
1000\
1000\
1100";

#endif 
