#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>
#include "../../brick_game/tetris/tetris.h"


UserAction_t getUserAction();
void print_overlay(const char *game_name);
void drawGameInfo(GameInfo_t *info);

#endif