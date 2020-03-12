#include <stdio.h>
#include "game.h"

Grid *Grid_Init()
{
    int size = GRID_WIDTH * GRID_HEIGHT;

    Grid *grid = malloc(sizeof(Grid));

    for (int i = 0; i <= size; i++){
        if (i % 2 == 0) grid->cells[i] = J;
        else if (i % 3 == 0) grid->cells[i] = O;
        else grid->cells[i] = Empty;
    }
    return grid;
}

SDL_Point Grid_IndexToCoords(int n)
{
    SDL_Point p;
    p.x = n % GRID_WIDTH;
    p.y = n/ GRID_WIDTH;
    return p;
}

int Grid_CoordsToIndex(SDL_Point p)
{
    return p.x + (p.y * GRID_WIDTH);
}

Piece Grid_PieceAtIndex(Grid *grid, int n)
{
    return grid->cells[n];
}

Piece Grid_PieceAtCoords(Grid *g, SDL_Point p)
{
    int n = Grid_CoordsToIndex(p);
    return Grid_PieceAtIndex(g, n);
}

GameState *GameState_Init()
{
    GameState *gameState = malloc(sizeof(GameState));
    gameState->dropping = false;
    gameState->playing = true;
    gameState->score = 0;
    gameState->grid = Grid_Init();
    return gameState;
}

bool GameState_Tick(GameState *gameState)
{
    gameState->playing = false;
    return true;
}
