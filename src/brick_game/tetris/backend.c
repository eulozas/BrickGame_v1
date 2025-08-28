#include "backend.h"
#include <stdlib.h>
#include <string.h>

// внутренняя структура (только в .c)
typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    int next[2][2];  // упрощённая заглушка для next-фигуры
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    int running;
} GameState;

static GameState game;  // глобальное внутреннее состояние

void initGame() {
    // обнуляем поле
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            game.field[y][x] = 0;
        }
    }
    game.score = 0;
    game.level = 1;
    game.speed = 1;
    game.pause = 0;
}

// ---------------- Вспомогательные функции ----------------
static int **allocMatrix(int h, int w) {
    int **m = malloc(h * sizeof(int *));
    for (int i = 0; i < h; i++) {
        m[i] = calloc(w, sizeof(int));
    }
    return m;
}

static void freeMatrix(int **m, int h) {
    if (!m) return;
    for (int i = 0; i < h; i++) {
        free(m[i]);
    }
    free(m);
}

static void resetGame() {
    memset(game.field, 0, sizeof(game.field));
    memset(game.next, 0, sizeof(game.next));
    game.score = 0;
    game.level = 1;
    game.speed = 1;
    game.pause = 0;
    game.running = 1;
}

// ---------------- API ----------------

// обработка пользовательского ввода
void userInput(UserAction_t action, bool hold) {
    switch (action) {
        case Start:
            resetGame();
            break;
        case Pause:
            game.pause = !game.pause;
            break;
        case Terminate:
            game.running = 0;
            break;
        case Left:
            // TODO: сдвинуть фигуру влево
            break;
        case Right:
            // TODO: сдвинуть фигуру вправо
            break;
        case Up:
            // TODO: поворот фигуры
            break;
        case Down:
            // TODO: ускоренное падение
            break;
        case Action:
            // TODO: "hard drop" или действие по заданию
            break;
    }
}

// получение копии текущего состояния игры
GameInfo_t updateCurrentState() {
    GameInfo_t info;

    // выделяем память для field
    info.field = allocMatrix(FIELD_HEIGHT, FIELD_WIDTH);
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            info.field[y][x] = game.field[y][x];
        }
    }

    // выделяем память для next (заглушка 2x2)
    info.next = allocMatrix(2, 2);
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            info.next[y][x] = game.next[y][x];
        }
    }

    info.score = game.score;
    info.high_score = game.high_score;
    info.level = game.level;
    info.speed = game.speed;
    info.pause = game.pause;

    return info;
}

// освобождение памяти у GameInfo_t
void freeGameInfo(GameInfo_t *info) {
    if (!info) return;
    freeMatrix(info->field, FIELD_HEIGHT);
    freeMatrix(info->next, 2);
    info->field = NULL;
    info->next = NULL;
}