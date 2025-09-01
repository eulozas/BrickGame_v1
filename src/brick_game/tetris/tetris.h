#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include "fsm.h"
#include "backend.h"
#include "../../gui/cli/frontend.h"

void init_ncurses();
void game_loop();

#endif