#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include "fsm.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

GameStruct_t *getGameState();
void freeGameInfo(GameInfo_t *info);
static int **alloc_and_copy_field(int src[FIELD_HEIGHT][FIELD_WIDTH]);
static int **alloc_and_copy_next(int src[4][4]);

#endif