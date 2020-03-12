#include "render.h"

SDL_Renderer *InitialiseRenderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return NULL;
    }
    SDL_Window *win = SDL_CreateWindow("Tetris", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        SDL_Quit();
        return NULL;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return NULL;
    }
    return ren;
}

void SetColor(SDL_Renderer *renderer, int hex)
{
    float r = ((hex >> 16) & 0xff);
    float g = ((hex >> 8) & 0xff);
    float b = ((hex >> 16) & 0xff);
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void ColorFromCell(SDL_Renderer *renderer, Piece p)
{
    switch (p)
    {
        case I:
            SetColor(renderer, LIGHTBLUE);
            break;
        case O:
            SetColor(renderer, YELLOW);
            break;
        case T:
            SetColor(renderer, PURPLE);
            break;
        case S:
            SetColor(renderer, GREEN);
            break;
        case Z:
            SetColor(renderer, RED);
            break;
        case J:
            SetColor(renderer, DARKBLUE);
            break;
        case L:
            SetColor(renderer, ORANGE);
            break;
    }
}

bool Draw_Grid(SDL_Renderer *renderer, Grid *g)
{
    float scalingX = 0.70;
    float scalingY = 1;
    int padding = 25;

    /* These values are what the ideal size of the grid would be but for the actual bounding box we do cellWidth * n 
        so that it always lines up perfectly. */
    float targetWidth = WIDTH * scalingX - (2 * padding);
    float targetHeight = HEIGHT * scalingY - (2 * padding);

    int cellWidth = targetWidth / GRID_WIDTH;
    int cellHeight = targetHeight / GRID_HEIGHT;

    SDL_Rect boundingBox = {
        .x = padding,
        .y = padding,
        .w = cellWidth * GRID_WIDTH,
        .h = cellHeight * GRID_HEIGHT};

    SetColor(renderer, WHITE);
    SDL_RenderDrawRect(renderer, &boundingBox);

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++)
    {
        if (g->cells[i] != Empty)
        {
            SDL_Point gridCoords = Grid_IndexToCoords(i);

            SDL_Rect cellRect = {
                .x = boundingBox.x + (gridCoords.x * cellWidth),
                .y = boundingBox.y + (gridCoords.y * cellHeight),
                .w = cellWidth,
                .h = cellHeight};

            SetColor(renderer, WHITE);
            SDL_RenderFillRect(renderer, &cellRect);

            int cellBorderPx = 1;
            cellRect.w -= 2 * cellBorderPx;
            cellRect.h -= 2 * cellBorderPx;
            cellRect.x += cellBorderPx;
            cellRect.y += cellBorderPx;
            
            ColorFromCell(renderer, g->cells[i]);
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    SetColor(renderer, BLACK);

    return true;
}

bool Draw_UI(SDL_Renderer *renderer, int score)
{
    return true;
}

void Draw_Guides(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xf0, 0xf0, 0xf0, 255);
    SDL_RenderDrawLine(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);
    SDL_RenderDrawLine(renderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

bool Draw_GameState(SDL_Renderer *renderer, GameState *g)
{
    SDL_RenderClear(renderer);
    // Draw_Guides(renderer);
    Draw_UI(renderer, g->score);
    Draw_Grid(renderer, g->grid);
    SDL_RenderPresent(renderer);
    return true;
}