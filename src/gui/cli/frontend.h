#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>
#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/fsm.h"

void print_overlay();
void print_center(int row, const char *msg);
void draw_game(GameInfo_t *state, state_t current_state);

#endif