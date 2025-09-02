#include "backend.h"
//#include "helpers.h"
#include <stdlib.h>
#include <string.h>

GameStruct_t *getGameStruct() {
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

GameInfo_t mallocGameInfo() {
    GameInfo_t info;

    info.field = malloc(FIELD_HEIGHT * sizeof(int *));
    for (int i = 0; i < FIELD_HEIGHT; i++)
        info.field[i] = malloc(FIELD_WIDTH * sizeof(int));

    info.next = malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++)
        info.next[i] = malloc(4 * sizeof(int));

    return info;
}

void copyGameInfo(GameStruct_t *game, GameInfo_t *info) {
    for (int i = 0; i < FIELD_HEIGHT; i++)
        for (int j = 0; j < FIELD_WIDTH; j++)
            info->field[i][j] = game->field[i][j];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            info->next[i][j] = game->next[i][j];

    info->score = game->score;
    info->high_score = game->high_score;
    info->level = game->level;
    info->speed = game->speed;
    info->pause = game->pause;
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

