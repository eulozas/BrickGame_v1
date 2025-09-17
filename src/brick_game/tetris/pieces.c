#include "pieces.h"

void draw_piece_to_field(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game->currentPiece[y][x]) {
                int fx = game->currentX + x;
                int fy = game->currentY + y;
                if (fy >= 0 && fy < FIELD_HEIGHT && fx >= 0 && fx < FIELD_WIDTH) game->field[fy][fx] = 2;
            }
        }
    }
}

void clear_piece_from_field(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game->currentPiece[y][x]){
                int fx = game->currentX + x;
                int fy = game->currentY + y;
                if (fy >= 0 && fy < FIELD_HEIGHT && fx >= 0 && fx < FIELD_WIDTH) {
                    if (game->field[fy][fx] == 2) game->field[fy][fx] = 0;
                }
            }  
        }
    }
}

int canSpawnPiece(GameStruct_t *game) {
    int exit_code = 1;
    for (int y = 0; y < 4 && exit_code != 0; y++) {
        for (int x = 0; x < 4 && exit_code != 0; x++) {
            if (game->currentPiece[y][x]){
                int fx = game->currentX + x;
                int fy = game->currentY + y;
                if (fy >= 0) {
                    if (game->field[fy][fx]) exit_code = 0;
                }
            }
        }
    }
    if(exit_code != 0) draw_piece_to_field(game);
    return exit_code;
}

void spawnNewPiece(GameStruct_t *game){
    memcpy(game->currentPiece, game->next, sizeof(int) * 16);
    game->currentX = FIELD_WIDTH / 2 - 2;
    game->currentY = -2;
    randomPiece(game->next);
}

int canMoveDown(const GameStruct_t *game) {
    int exit_code = 1;
    for (int y = 0; y < 4 && exit_code != 0; y++) {
        for (int x = 0; x < 4 && exit_code != 0; x++) {
            if (game->currentPiece[y][x]){
                int fx = game->currentX + x;
                int fy = game->currentY + y + 1;
                if (fy >= FIELD_HEIGHT || (fy >= 0 && game->field[fy][fx] == 1)) exit_code = 0; 
            } 
        }
    }
    return exit_code;
}

void autoMoveDown(GameStruct_t *game){
    clear_piece_from_field(game);
    game->currentY++;
    draw_piece_to_field(game);
}

void moveDown(GameStruct_t *game) {
    clear_piece_from_field(game);
        while (canMoveDown(game)) {
            game->currentY++;
        }
    draw_piece_to_field(game);
}

int canMoveLeft(const GameStruct_t *game) {
    int exit_code = 1;
    for (int y = 0; y < 4 && exit_code != 0; y++) {
        for (int x = 0; x < 4 && exit_code != 0; x++) {
            if (game->currentPiece[y][x]){
                int fx = game->currentX + x - 1;
                int fy = game->currentY + y;
                if (fx < 0 || (fy >= 0 && game->field[fy][fx] == 1)) exit_code = 0;
            }
        }
    }
    return exit_code;
}

void moveLeft(GameStruct_t *game) {
    clear_piece_from_field(game);
    if (canMoveLeft(game)) game->currentX--;
    draw_piece_to_field(game);
}

int canMoveRight(const GameStruct_t *game) {
    int exit_code = 1;
    for (int y = 0; y < 4 && exit_code != 0; y++) {
        for (int x = 0; x < 4 && exit_code != 0; x++) {
            if (game->currentPiece[y][x]){
                int fx = game->currentX + x + 1;
                int fy = game->currentY + y;
                if (fx >= FIELD_WIDTH || (fy >= 0 && game->field[fy][fx] == 1)) exit_code = 0;
            } 
        }
    }
    return exit_code;
}

void moveRight(GameStruct_t *game) {
    clear_piece_from_field(game);
    if (canMoveRight(game)) game->currentX++;
    draw_piece_to_field(game);
}

int canRotate(const GameStruct_t *game, const int rotated[4][4], int offsetX, int offsetY) {
    int exit_code = 1;
    for (int y = 0; y < 4 && exit_code != 0; y++) {
        for (int x = 0; x < 4 && exit_code != 0; x++) {
            if (rotated[y][x]){
                int fx = game->currentX + x + offsetX;
                int fy = game->currentY + y + offsetY;
                if (fx < 0 || fx >= FIELD_WIDTH || fy >= FIELD_HEIGHT || (fy >= 0 && game->field[fy][fx] == 1)) exit_code = 0;
            } 
        }
    }
    return exit_code;
}

void rotatePiece(GameStruct_t *game) {
    int rotated[4][4] = {0};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            rotated[x][3 - y] = game->currentPiece[y][x];
        }
    }

    // сдвиги
    int kicks[][2] = {
        {0, 0},   // как есть
        {-1, 0},  // сдвиг влево
        {1, 0},   // сдвиг вправо
        {-2, 0},  // чуть дальше влево
        {2, 0},   // чуть дальше вправо
        {0, -1},  // иногда нужен сдвиг вверх
    };

    int was_rotated = 0;

    for (unsigned int i = 0; i < sizeof(kicks)/sizeof(kicks[0]) && !was_rotated; i++) {
        int dx = kicks[i][0];
        int dy = kicks[i][1];

        if (canRotate(game, (const int (*)[4])rotated, dx, dy)) {
            clear_piece_from_field(game);
            memcpy(game->currentPiece, rotated, sizeof(rotated));
            game->currentX += dx;
            game->currentY += dy;
            draw_piece_to_field(game);
            was_rotated = 1;
        }
    }
}

void attachPiece(GameStruct_t *game) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game->currentPiece[y][x]){
                int fx = game->currentX + x;
                int fy = game->currentY + y;
                if (fy >= 0 && fy < FIELD_HEIGHT && fx >= 0 && fx < FIELD_WIDTH) game->field[fy][fx] = 1; 
            } 
        }
    }
}

int clearLines(GameStruct_t *game) {
    int lines_cleared = 0;

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        int full = 1;
        for (int x = 0; x < FIELD_WIDTH && full; x++) {
            if (game->field[y][x] == 0) full = 0;
        }
        if (full) {
            for (int ty = y; ty > 0; ty--) {
                for (int x = 0; x < FIELD_WIDTH; x++)
                    game->field[ty][x] = game->field[ty-1][x];
            }
            for (int x = 0; x < FIELD_WIDTH; x++) game->field[0][x] = 0;

            lines_cleared++;
            y--;
        }
    }
    return lines_cleared;
}

void updateScore(GameStruct_t *game, int lines_cleared) {
    switch (lines_cleared) {
        case 1: game->score += 100; break;
        case 2: game->score += 300; break;
        case 3: game->score += 700; break;
        case 4: game->score += 1500; break;
        default: break;
    }
}

void updateLevel(GameStruct_t *game) {
    int new_level = (game->score / 600) + 1;
    if (new_level > game->level) {
        game->level = new_level > 10 ? 10 : new_level;
        game->fall_delay = FALL_DELAY - (game->level * 100);
        if (game->fall_delay < 100) game->fall_delay = 100;
    }
    game->speed = game->level;
}

void updateHighScore(GameStruct_t *game) {
    if (game->score > game->high_score) {
        game->high_score = game->score;
        saveHighScore(game->high_score);
    }
}

void processCompletedLines(GameStruct_t *game) {
    int lines_cleared = clearLines(game);
    if (lines_cleared > 0) {
        updateScore(game, lines_cleared);
        updateLevel(game);
        updateHighScore(game);
    }
}

void randomPiece(int dest[4][4]) {
    int idx = rand() % NUM_TETROMINOS;
    memcpy(dest, tetrominos[idx], sizeof(int) * 16);
}