#ifndef BACKEND_H
#define BACKEND_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include "types.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

#define FALL_DELAY 1200

typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    int currentPiece[4][4]; // текущая фигура
    int next[4][4];  // next-фигура
    int currentX, currentY;  
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    int running;
    tet_state state;
    long last_fall_time;   // когда в последний раз падала фигура
    long fall_delay;       // интервал между падениями (мс)
} GameStruct_t;

GameStruct_t *getGameStruct();
GameInfo_t mallocGameInfo();
void copyGameInfo(GameStruct_t *game, GameInfo_t *info);
void freeGameInfo(GameInfo_t *info);
void restartGameStruct(GameStruct_t *game);
void clearField(GameStruct_t *game);
long getCurrentTimeMs();

#endif