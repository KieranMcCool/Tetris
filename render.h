/* This header defines all the core methods and functionality for the rendering of the game */ 
#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "game.h"

#define FPS 60

#define WIDTH 600
#define HEIGHT 800

#define BLACK       0x000000
#define WHITE       0xffffff
#define LIGHTBLUE   0x00fff7
#define DARKBLUE    0x002aff
#define ORANGE      0xff8c00
#define YELLOW      0xff8c00
#define GREEN       0x33ff00
#define PURPLE      0xf700ff
#define RED         0Xff0000

SDL_Renderer *InitialiseRenderer();
bool Draw_Grid(SDL_Renderer *renderer, Grid *g);
bool Draw_UI(SDL_Renderer *renderer, int score);
bool Draw_GameState(SDL_Renderer *renderer, GameState *g);

#endif