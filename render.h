/* This header defines all the core methods and functionality for the rendering of the game */ 
#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "game.h"

#define WIDTH 640
#define HEIGHT 800

SDL_Renderer *initialiseRenderer();
bool Draw_Grid(Grid *g);
bool Draw_UI(int score);
bool Draw_GameState(GameState *g);

#endif