#include "render.h"

SDL_Renderer *InitialiseRenderer(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        return NULL;
    }
    SDL_Window *win = SDL_CreateWindow("Tetris", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL){
        SDL_Quit();
        return NULL;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        SDL_Quit();
        return NULL;
    }
    return ren;
}

bool Draw_Grid(SDL_Renderer *renderer, Grid *g) 
{
    int padding = 50;
    float scalingX = 1.3;
    int scalingY = 1;

    /* These values are what the ideal size of the grid would be but for the actual bounding box we do cellWidth * n 
        so that it always lines up perfectly. */
    int targetWidth = WIDTH  / scalingX - (2 * padding);
    int targetHeight = HEIGHT / scalingY - (2 * padding);

    int cellWidth = targetWidth / GRID_WIDTH;
    int cellHeight = targetHeight / GRID_HEIGHT;

    SDL_Rect boundingBox = { 
        .x = padding, 
        .y = padding, 
        .w = cellWidth * GRID_WIDTH, 
        .h = cellHeight * GRID_HEIGHT
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &boundingBox);

    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++)
    {
        if (g->cells[i] == Empty)
        {
            SDL_Point gridCoords = Grid_IndexToCoords(i);

            SDL_Rect cellRect = { 
                .x = boundingBox.x + (gridCoords.x * cellWidth), 
                .y = boundingBox.y = (gridCoords.y * cellHeight) + padding, 
                .w = cellWidth, 
                .h = cellHeight
            };

            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    return true;
}

bool Draw_UI(SDL_Renderer *renderer, int score) 
{
    return true;
}

void Draw_Guides(SDL_Renderer *renderer) 
{
    SDL_SetRenderDrawColor(renderer, 0xf0, 0xf0, 0xf0, 255);
    SDL_RenderDrawLine(renderer, 0, HEIGHT/2, WIDTH, HEIGHT/2);
    SDL_RenderDrawLine(renderer, WIDTH/2, 0, WIDTH/2, HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

bool Draw_GameState(SDL_Renderer *renderer, GameState *g) 
{
    SDL_RenderClear(renderer);
    Draw_Guides(renderer);
    Draw_UI(renderer, g->score);
    Draw_Grid(renderer, g->grid);
    SDL_RenderPresent(renderer);
    return true;
}