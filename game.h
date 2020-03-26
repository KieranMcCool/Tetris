/* This Header defines all the data structures and method for the core game logic. */
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL.h>
#include <string.h>

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

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

typedef struct gameState {
    Grid *grid;
    int score;
    bool dropping;
    bool playing;
    uint32_t tick;
    int gameSpeed;
} GameState;

GameState *GameState_Init();
void GameState_Tick(GameState *gameState);

//  I, O, T, S, Z, J, L, Empty

static char IPiece[] = 
"0100\
0100\
0100\
0100";

static char OPiece[] = 
"1100\
1100\
0000\
0000";

static char TPiece[] = 
"0100\
1110\
0000\
0000";

static char SPiece[] = 
"0011\
0110\
0000\
0000";

static char ZPiece[] = 
"1100\
0110\
0000\
0000";

static char JPiece[] = 
"0100\
0100\
0100\
0110";

static char LPiece[] = 
"0100\
0100\
0100\
0110";

#endif 