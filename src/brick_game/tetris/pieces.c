#include "pieces.h"

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

void spawn_new_piece(GameStruct_t *game){
    memcpy(game->currentPiece, game->next, sizeof(int) * 16);
    game->currentX = FIELD_WIDTH / 2 - 2;
    game->currentY = -2;
    randomPiece(game->next);
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

void move_piece_down(GameStruct_t *game){
    clear_piece_from_field(game);
    game->currentY++;
    draw_piece_to_field(game);
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