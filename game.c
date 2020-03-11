#include <stdio.h>
#include "game.h"

Grid *Grid_Init()
{
    int size = sizeof(int) * GRID_WIDTH * GRID_HEIGHT;
    Grid *grid = malloc(size);
    for (int i; i <= size; i++){
        grid->cells[i] = Empty;
    }
    return grid;
}

SDL_Point Grid_IndexToCoords(int n)
{

}

int Grid_CoordsToIndex(SDL_Point p)
{

}

Piece Grid_PieceAtIndex(int n)
{

}

Piece Grid_PieceAtCoords(SDL_Point p)
{

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

}
