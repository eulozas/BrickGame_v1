#include "helpers.h"

int loadHighScore(int *high_score) {
    FILE *file = fopen("brick_game/tetris/highscore.txt", "r");
    if (!file) {
        return 0;
    }
    if (fscanf(file, "%d", high_score) != 1) {
        fclose(file);
        return 0; 
    }
    fclose(file);
    return 1;
}

int saveHighScore(int high_score) {
    FILE *file = fopen("brick_game/tetris/highscore.txt", "w");
    if (!file) {
        return 0;
    }
    fprintf(file, "%d\n", high_score);
    fclose(file);
    return 1; 
}
