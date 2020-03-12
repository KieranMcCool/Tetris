/* This header defines all the core methods and functionality for the rendering of the game */ 
#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "game.h"

#define WIDTH 640
#define HEIGHT 800

SDL_Renderer *InitialiseRenderer();
bool Draw_Grid(SDL_Renderer *renderer, Grid *g);
bool Draw_UI(SDL_Renderer *renderer, int score);
bool Draw_GameState(SDL_Renderer *renderer, GameState *g);

#endif