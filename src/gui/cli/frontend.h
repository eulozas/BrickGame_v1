#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/types.h"

//ncurses
void init_ncurses();
void end_ncurses();
void block_input_ncurses();
void noblock_input_ncurses();
void delay_ncurses(int ms);

UserAction_t getUserAction();
void printOverlay(const char *game_name);
void drawGameInfo(GameInfo_t *info);

#endif