#include <SDL.h>
#include <stdbool.h>
#include "game.h"
#include "render.h"

char pollEvent()
{
    char c;
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            c = 'q';
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case 'w':
                c = c == 'd' ? 'd' : 'u';
                break;
            case 's':
                c = c == 'u' ? 'u' : 'd';
                break;
            case 'a':
                c = c == 'r' ? 'r' : 'l';
                break;
            case 'd':
                c = c == 'l' ? 'l' : 'r';
                break;
            default:
                break;
            }
        }
    }

    return c;
}

bool handleInput() {
    bool cont = true;
    char event = pollEvent();
    if (event) {
        switch (event){
            case 'q':
                cont = false;
                break;
            case 'u':
                break;
            case 'l':
                break;
            case 'd':
                break;
            case 'r':
                break;
        }
    }
    return cont;
}

int main()
{
    SDL_Renderer *rend = initialiseRenderer();
    bool running = true;
    SDL_RenderPresent(rend);

    while (running)
    {
        SDL_RenderClear(rend);
        running = handleInput();
        
        if (running)
        {


            SDL_RenderPresent(rend);
        }
    }

    return 1;
}
