#include "input.h"

Action Input_PollEvent()
{
    Action action = NONE;
    SDL_Event e;
    if (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            action = QUIT;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case 'w':
                    action = UP;
                    break;
                case 's':
                    action = DOWN;
                    break;
                case 'a':
                    action = LEFT;
                    break;
                case 'd':
                    action = RIGHT; 
                    break;
                case 'e':
                    action = ROTATE;
                    break;
                default:
                    break;
            }
        }
    }

    return action;
}


