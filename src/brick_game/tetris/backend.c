#define _POSIX_C_SOURCE 199309L 
#include "backend.h"
#include "helpers.h"
#include <stdlib.h>
#include <string.h>

long getCurrentTimeMs(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

// ФИГУРЫ и действия, потом убрать в другой файл

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

void draw_piece_to_field(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game->currentPiece[y][x]) {
                int fx = game->currentX + x;
                int fy = game->currentY + y;
                if (fy >= 0 && fy < FIELD_HEIGHT &&
                    fx >= 0 && fx < FIELD_WIDTH) {
                    game->field[fy][fx] = 2; //подумать, может без 2, еще поле(?)
                }
            }
        }
    }
}

int canSpawnPiece(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game->currentPiece[y][x]) continue; 

            int fx = game->currentX + x;
            int fy = game->currentY + y;
            if (fx < 0 || fx >= FIELD_WIDTH) {
                return 0;
            }
            if (fy >= FIELD_HEIGHT) {
                return 0;
            }
            if (fy >= 0) {
                if (game->field[fy][fx]) return 0;
            }
        }
    }
    draw_piece_to_field(game);
    return 1;
}

int canMoveDown(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (!game->currentPiece[y][x]) continue;

            int fx = game->currentX + x;
            int fy = game->currentY + y + 1;

            if (fy >= FIELD_HEIGHT) return 0;
            if (fy >= 0 && game->field[fy][fx] == 1) return 0; 
        }
    }
    return 1;
}

void removeLine(GameStruct_t *game) {
    int lines_cleared = 0;

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        int full = 1;
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (game->field[y][x] == 0) {
                full = 0;
                break;
            }
        }

        if (full) {
            // сдвигаем все строки вниз
            for (int ty = y; ty > 0; ty--) {
                for (int x = 0; x < FIELD_WIDTH; x++) {
                    game->field[ty][x] = game->field[ty-1][x];
                }
            }
            // обнуляем верхнюю строку
            for (int x = 0; x < FIELD_WIDTH; x++) {
                game->field[0][x] = 0;
            }

            lines_cleared++;
            y--; 
        }
    }

    switch (lines_cleared) {
        case 1: game->score += 100; break;
        case 2: game->score += 300; break;
        case 3: game->score += 700; break;
        case 4: game->score += 1500; break;
        default: break;
    }

    if (game->score > game->high_score) {
        game->high_score = game->score;
        saveHighScore(game->high_score); 
    }
}

void randomPiece(int dest[4][4]) {
    int idx = rand() % NUM_TETROMINOS;
    memcpy(dest, tetrominos[idx], sizeof(int) * 16);
}

void clear_piece_from_field(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (!game->currentPiece[y][x]) continue;
            int fx = game->currentX + x;
            int fy = game->currentY + y;
            if (fy >= 0 && fy < FIELD_HEIGHT && fx >= 0 && fx < FIELD_WIDTH) {
                if (game->field[fy][fx] == 2) 
                    game->field[fy][fx] = 0;
            }
        }
    }
}

void attachPiece(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (!game->currentPiece[y][x]) continue;
            int fx = game->currentX + x;
            int fy = game->currentY + y;
            if (fy >= 0 && fy < FIELD_HEIGHT && fx >= 0 && fx < FIELD_WIDTH) {
                game->field[fy][fx] = 1; 
            }
        }
    }
}

void spawn_new_piece(GameStruct_t *game){
    memcpy(game->currentPiece, game->next, sizeof(int) * 16);
    game->currentX = FIELD_WIDTH / 2 - 2;
    game->currentY = -2;
    randomPiece(game->next);
}

void move_piece_down(GameStruct_t *game){
    clear_piece_from_field(game);
    game->currentY++;
    draw_piece_to_field(game);
}



//КОНЕЦ ФИГУР 




static void initGameStruct(GameStruct_t *game){
    memset(game, 0, sizeof(GameStruct_t));
    game->score = 0;
    game->level = 0;
    game->speed = 0;
    game->pause = 0;
    game->running = 1;
    game->state = START;
    game->last_fall_time = getCurrentTimeMs();
    game->fall_delay = 100; // 0.8 секунды

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

