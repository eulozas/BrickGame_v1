#include "helpers.h"

int loadHighScore(int *high_score) {
    FILE *file = fopen("brick_game/tetris/highscore.txt", "r");
    if (!file) {
        return 0;  // файла нет или ошибка открытия
    }

    if (fscanf(file, "%d", high_score) != 1) {
        fclose(file);
        return 0;  // не удалось считать число
    }

    fclose(file);
    return 1;
}

int saveHighScore(int high_score) {
    FILE *file = fopen("highscore.txt", "w");
    if (!file) {
        // не удалось открыть файл для записи
        return 0;
    }

    fprintf(file, "%d\n", high_score);
    fclose(file);
    return 1; // успех
}

