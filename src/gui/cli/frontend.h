#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>
#include "../../brick_game/tetris/types.h"

UserAction_t getUserAction();
void printOverlay(const char *game_name);
void drawGameInfo(GameInfo_t *info);

#endif