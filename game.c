#include <stdio.h>
#include "game.h"
#include "render.h"

Grid *Grid_Init()
{
    Grid *grid = malloc(sizeof(Grid));

    int size = GRID_WIDTH * GRID_HEIGHT;

    for (int i = 0; i < size; i++)
    {
        grid->cells[i] = Empty;
        grid->cellsActiveState[i] = false;
    }

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

bool Grid_IndexIsActive(Grid *grid, int i)
{
    return grid->cellsActiveState[i];
}

bool Grid_CoordIsActive(Grid *grid, SDL_Point p)
{
    int index = Grid_CoordsToIndex(p);
    return Grid_IndexIsActive(grid, index);
}

void Grid_ClearActiveStates(Grid *grid)
{
    int size = GRID_HEIGHT * GRID_WIDTH;
    for (int i = 0; i <= size; i++)
    {
        grid->cellsActiveState[i] = false;
    }
}

void Grid_SpawnPiece(Grid *grid) 
{
    int randomPiece = rand() % 7;
    Piece piece;
    char *pieceData;

    switch (randomPiece)
    {
        case 0: piece = I; pieceData = IPiece; break;
        case 1: piece = O; pieceData = OPiece; break;
        case 2: piece = T; pieceData = TPiece; break;
        case 3: piece = S; pieceData = SPiece; break;
        case 4: piece = Z; pieceData = ZPiece; break;
        case 5: piece = J; pieceData = JPiece; break;
        case 6: piece = L; pieceData = LPiece; break;
    }

    int xOffset = (GRID_WIDTH / 2) - 1;
    int yOffset = 0;

    for (size_t i = 0; i <= strlen(pieceData); i++) 
    {
        if (pieceData[i] == '1')
        {
            int x = (i % 4) + xOffset;
            int y = (i / 4) + yOffset;
            SDL_Point p = { .x=x, .y=y };
            int index = Grid_CoordsToIndex(p);
            grid->cells[index] = piece;
            grid->cellsActiveState[index] = true;
        }
    }
}

GameState *GameState_Init()
{
    GameState *gameState = malloc(sizeof(GameState));
    gameState->dropping = false;
    gameState->playing = true;
    gameState->score = 0;
    gameState->tick = 0;
    gameState->gameSpeed = 10;
    gameState->grid = Grid_Init();
    return gameState;
}

void GameState_ClearLines(GameState *gameState)
{
    int lineClears = 0;
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        bool gap = false;

        for (int x = 0; x < GRID_WIDTH; x++)
        {
            SDL_Point p = {.x = x, .y = y};
            Piece piece = Grid_PieceAtCoords(gameState->grid, p);

            if (piece == Empty)
            {
                gap = true;
            }
        }

        if (!gap)
        {
            for (int x = 0; x <= GRID_WIDTH; x++)
            {
                SDL_Point p = {.x = x, .y = y};
                Piece piece = Grid_PieceAtCoords(gameState->grid, p);
                gameState->grid->cells[Grid_CoordsToIndex(p)] = Empty;
                lineClears++;
            }
        }
    }

    switch (lineClears)
    {
        case 1:
            gameState->score += 50 * (gameState->gameSpeed + 1);
            break;
        case 2: 
            gameState->score += 150 * (gameState->gameSpeed + 1);
            break;
        case 3: 
            gameState->score += 350 * (gameState->gameSpeed + 1);
            break;
        case 4: 
            gameState->score += 100 * (gameState->gameSpeed + 1);
            break;
    }
}

void GameState_Gravity(GameState *gameState)
{
    Grid *grid = gameState->grid;
    int size = GRID_WIDTH * GRID_HEIGHT;

    bool hitBottom = false;
    int reverseFrom;

    for (int i = size; i >= 0; i--)
    {
        if (Grid_IndexIsActive(gameState->grid, i))
        {
            SDL_Point coords = Grid_IndexToCoords(i);
            SDL_Point belowCoords = {.x = coords.x, .y = coords.y + 1};

            grid->cellsActiveState[i] = false;

            if (belowCoords.y < GRID_HEIGHT)
            {
                int belowIndex = Grid_CoordsToIndex(belowCoords);

                if (Grid_PieceAtIndex(gameState->grid, belowIndex) == Empty && !hitBottom)
                {
                    grid->cells[belowIndex] = grid->cells[i];
                    grid->cellsActiveState[belowIndex] = true;
                    grid->cells[i] = Empty;
                    gameState->droppedBlocks++;
                }
                else
                {
                    hitBottom = true;
                    reverseFrom = belowIndex - 1;
                    break;
                }
            }
        }
    }

    if (hitBottom)
    {
        for (int i = size; i > reverseFrom; i--)
        {
            SDL_Point coords = Grid_IndexToCoords(i);

            if (Grid_CoordIsActive(gameState->grid, coords))
            {
                grid->cellsActiveState[i] = false;
                SDL_Point aboveCoords = {.x = coords.x, .y = coords.y - 1};
                int aboveIndex = Grid_CoordsToIndex(aboveCoords);
                grid->cells[aboveIndex] = grid->cells[i];
                grid->cells[i] = Empty;
            }
        }

        Grid_ClearActiveStates(grid);

        gameState->dropping = false;
    }
}

void GameState_NextPiece(GameState *gameState)
{
    if (!gameState->dropping)
    {
        gameState->score = gameState->score + (10 * gameState->gameSpeed + 1);
        gameState->dropping = true;
        gameState->droppedBlocks = 0;
        Grid_SpawnPiece(gameState->grid);
    }
}

void GameState_CheckLoss(GameState *gameState)
{
    if (!gameState->dropping && gameState->droppedBlocks == 0)
    {
        gameState->playing = false;
    }
}

bool GameState_BoardIsClear(GameState *gameState)
{
    for (int i = 0; i <= GRID_HEIGHT * GRID_WIDTH; i++)
    {
       if (gameState->grid->cells[i] != Empty) return false;
    }

    return true;
}

void GameState_Tick(GameState *gameState)
{
    gameState->tick++;
    int modTargetFrame = FPS / gameState->gameSpeed;
    if (gameState->tick % modTargetFrame == 0 && gameState->playing)
    {
        GameState_Gravity(gameState);
        GameState_ClearLines(gameState);
        GameState_CheckLoss(gameState);

        if (GameState_BoardIsClear(gameState))
        {
            //Clear the board = 2000*(level + 1)
            gameState->score = gameState->score + (2000 * (gameState->gameSpeed + 1));
        }

        GameState_NextPiece(gameState);

    }
}

void GameState_ProcessInput(Action action, GameState *gameState) 
{
    if (action == QUIT) {
        gameState->playing = false;
    }
}
