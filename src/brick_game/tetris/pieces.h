#ifndef PIECES_H
#define PIECES_H

#include "backend.h"
#include "helpers.h"

#define NUM_TETROMINOS 7

static const int tetrominos[NUM_TETROMINOS][4][4] = {
    // I
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    // O
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    // T
    {
        {0,0,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    },
    // S
    {
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0}
    },
    // Z
    {
        {0,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    // J
    {
        {0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    // L
    {
        {0,0,0,0},
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0}
    }
};

int canSpawnPiece(GameStruct_t *game);
void spawnNewPiece(GameStruct_t *game);
int canMoveDown(GameStruct_t *game);
void autoMoveDown(GameStruct_t *game);
void moveDown(GameStruct_t *game);
void moveLeft(GameStruct_t *game);
void moveRight(GameStruct_t *game);
void removeLine(GameStruct_t *game);
void attachPiece(GameStruct_t *game);
void randomPiece(int dest[4][4]);

#endif