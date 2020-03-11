#include <SDL.h>
#include <stdbool.h>
#include "game.h"
#include "render.h"

char PollEvent()
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

int main()
{
    SDL_Renderer *rend = initialiseRenderer();
    bool running = true;
    SDL_RenderPresent(rend);

    GameState *game = GameState_Init();

    while (game->playing)
    {
        PollEvent();
        GameState_Tick();
        Draw_GameState(game);
    }

    return 1;
}
