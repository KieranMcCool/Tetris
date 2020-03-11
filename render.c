#include "render.h"

SDL_Renderer * initialiseRenderer(){
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


bool Draw_Grid(Grid *g) 
{
    return true;
}

bool Draw_UI(int score) 
{
    return true;
}

bool Draw_GameState(GameState *g) 
{
    return true;
}