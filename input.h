#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

typedef enum action { UP, DOWN, LEFT, RIGHT, A, B, START, SELECT, ROTATE, NONE, QUIT } Action;

// Polls for an keyboard/mouse interaction.
Action Input_PollEvent();

#endif
