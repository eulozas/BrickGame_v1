#include "backend.h"
#include "helpers.h"
#include <stdlib.h>
#include <string.h>

GameStruct_t *getGameState() {
    static GameStruct_t game;  
    static int initialized = 0;

    if (!initialized) {
        memset(&game, 0, sizeof(GameStruct_t));
        game.running = 1;
        game.level = 1;
        game.speed = 1;
        game.pause = 0;
        game.last_fall_time = 0;
        game.fall_delay = 1000; // 1 секунда

        if (/*loadHighScore(&game.high_score)*/1) {//функция загрузки данных из файла
            game.state = START;
        } else {
            game.high_score = 0;
            game.state = FILE_ERROR_STATE;
        }

        initialized = 1;
    }

    return &game;
}


static int **alloc_and_copy_field(int src[FIELD_HEIGHT][FIELD_WIDTH]) {
    int **dst = malloc(FIELD_HEIGHT * sizeof(int *));
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        dst[i] = malloc(FIELD_WIDTH * sizeof(int));
        memcpy(dst[i], src[i], FIELD_WIDTH * sizeof(int));
    }
    return dst;
}

static int **alloc_and_copy_next(int src[4][4]) {
    int **dst = malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++) {
        dst[i] = malloc(4 * sizeof(int));
        memcpy(dst[i], src[i], 4 * sizeof(int));
    }
    return dst;
}

void freeGameInfo(GameInfo_t *info) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        free(info->field[i]);
    }
    free(info->field);

    for (int i = 0; i < 4; i++) {
        free(info->next[i]);
    }
    free(info->next);

    info->field = NULL;
    info->next = NULL;
}

