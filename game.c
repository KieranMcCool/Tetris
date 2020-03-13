#include <stdio.h>
#include "game.h"

Grid *Grid_Init()
{

    Grid *grid = malloc(sizeof(Grid));

    int size = GRID_WIDTH * GRID_HEIGHT;
    
    for (int i = 0; i < size; i++)
    {
        grid->cells[i] = Empty;
    }

    grid->cells[1] = I;
    grid->cells[2] = O;
    grid->cells[3] = T;
    grid->cells[4] = S;
    grid->cells[5] = Z;
    grid->cells[6] = J;
    grid->cells[7] = L;
    grid->cells[size - 1] = O;

    return grid;
}

SDL_Point Grid_IndexToCoords(int n)
{
    SDL_Point p;
    p.x = n % GRID_WIDTH;
    p.y = n / GRID_WIDTH;
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
    gameState->tick = 0;
    gameState->gameSpeed = 20;
    gameState->grid = Grid_Init();
    return gameState;
}

void GameState_Tick(GameState *gameState)
{
    gameState->tick++;
    if (gameState->tick % gameState->gameSpeed == 0)
    {
        Grid *grid = gameState->grid;
        int size = GRID_WIDTH * GRID_HEIGHT;

        for (int i = size - 2; i > 0; i--)
        {
            if (grid->cells[i] != Empty) 
            {
                SDL_Point coords = Grid_IndexToCoords(i);
                SDL_Point belowCoords = {.x = coords.x, .y = coords.y + 1};

                if (belowCoords.y < GRID_HEIGHT) 
                {
                    int belowIndex = Grid_CoordsToIndex(belowCoords);
                    if (grid->cells[belowIndex] == Empty) 
                    {
                        grid->cells[belowIndex] = grid->cells[i];
                        grid->cells[i] = Empty;
                    }
                }
            }
        }
    }
}
