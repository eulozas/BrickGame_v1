#include "backend.h"
#include "pieces.h"

static void initGameStruct(GameStruct_t *game){
    memset(game, 0, sizeof(GameStruct_t));
    game->score = 0;
    game->level = 0;
    game->speed = 0;
    game->pause = 0;
    game->running = 1;
    game->state = START;
    game->last_fall_time = getCurrentTimeMs();
    game->fall_delay = 1200; // 0.8 секунды

    srand(time(NULL));
    randomPiece(game->next);
    if (!loadHighScore(&game->high_score)) {
        game->high_score = -1;
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

void clearField(GameStruct_t *game){
    for (int i = 0; i < FIELD_HEIGHT; i++)
        for (int j = 0; j < FIELD_WIDTH; j++)
            game->field[i][j] = 0;
}

GameInfo_t mallocGameInfo() {
    GameInfo_t info;

    info.field = NULL;
    info.next = NULL;
    info.score = 0;
    info.high_score = 0;
    info.level = 0;
    info.speed = 0;
    info.pause = 0;

    info.field = malloc(FIELD_HEIGHT * sizeof(int *));
    if (info.field) {
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            info.field[i] = malloc(FIELD_WIDTH * sizeof(int));
            if (!info.field[i]) {
                for (int j = 0; j < i; j++) free(info.field[j]);
                free(info.field);
                info.field = NULL;
                break;
            }
        }
    }

    if(info.field){
        info.next = malloc(4 * sizeof(int *));
        if (info.next) {
            for (int i = 0; i < 4; i++) {
                info.next[i] = malloc(4 * sizeof(int));
                if (!info.next[i]) {
                    for (int j = 0; j < i; j++) free(info.next[j]);
                    free(info.next);
                    info.next = NULL;
                    break;
                }
            }
        }else{
            freeGameInfo(&info);
        }
    }
    return info;
}

void copyGameInfo(GameStruct_t *game, GameInfo_t *info) {
     if (info->field == NULL) {
        game->running = 0;
        return;
    }
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
    if (!info) return;

    if (info->field) {
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            free(info->field[i]); 
        }
        free(info->field);
        info->field = NULL;
    }

    if (info->next) {
        for (int i = 0; i < 4; i++) {
            free(info->next[i]);
        }
        free(info->next);
        info->next = NULL;
    }
}

long getCurrentTimeMs(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}