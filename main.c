#include <SDL.h>
#include <stdbool.h>
#include "game.h"
#include "render.h"
#include "input.h"

int main()
{
    srand(time(NULL));
    SDL_Renderer *rend = InitialiseRenderer();
    GameState *game = GameState_Init();
    uint32_t targetTicks = 1000 / FPS;

    while (game->playing)
    {
        uint32_t startTicks = SDL_GetTicks();
        Action inputAction = Input_PollEvent();
        GameState_ProcessInput(inputAction, game);
        if (game->playing)
        {
            GameState_Tick(game);
            Draw_GameState(rend, game);
            uint32_t endTicks = SDL_GetTicks();
            uint32_t totalTicks = endTicks - startTicks;
            if (totalTicks < targetTicks) 
            {
                SDL_Delay(targetTicks - totalTicks);
            }
        }
    }

    SDL_DestroyRenderer(rend);
    return 1;
}
