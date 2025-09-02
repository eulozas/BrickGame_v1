#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>
#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/fsm.h"


UserAction_t getUserAction();
void print_overlay();
void print_center(int row, const char *msg);
void draw_game(GameInfo_t *state, tet_state current_state);

#endif