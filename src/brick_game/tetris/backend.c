#include "backend.h"
//#include "helpers.h"
#include <stdlib.h>
#include <string.h>

static void initGameStruct(GameStruct_t *game){
    memset(game, 0, sizeof(GameStruct_t));
    game->running = 1;
    game->level = 0;
    game->speed = 1;
    game->pause = 0;
    game->last_fall_time = 0;
    game->fall_delay = 1000; // 1 секунда

    if (/*loadHighScore(&game->high_score)*/1) { //проверка загрузки файла с рекордом игры
        game->state = START;
        game->high_score = 0;//тут будет функция, которая запишет в этц переменную рекорд игры
    } else {
        game->state = FILE_ERROR_STATE;
    }
}

GameStruct_t *getGameStruct() {
    static GameStruct_t game;  
    static int init_game = 0;

    if (!init_game) {
        initGameStruct(&game);
        init_game = 1;
    }

    return &game;
}

void restartGameStruct(GameStruct_t *game){
    initGameStruct(game);
}

GameInfo_t mallocGameInfo() {
    GameInfo_t info;

    info.field = malloc(FIELD_HEIGHT * sizeof(int *));
    for (int i = 0; i < FIELD_HEIGHT; i++)
        info.field[i] = malloc(FIELD_WIDTH * sizeof(int));

    info.next = malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++)
        info.next[i] = malloc(4 * sizeof(int));

    info.score = 0;
    info.high_score = 0;
    info.level = 0;
    info.speed = 0;
    info.pause = 0;

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

    if (!info || !info->field || !info->next) return;
    
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

