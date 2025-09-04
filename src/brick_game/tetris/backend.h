#ifndef BACKEND_H
#define BACKEND_H

#include "types.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    int next[4][4];  // next-фигура
    //int currentPiece[4][4]; // текущая фигура
    //int currentX, currentY;  
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

#endif