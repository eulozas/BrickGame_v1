#include "helpers.h"

int loadHighScore(int *high_score) {
  int exit_code = 1;
  FILE *file = fopen("brick_game/tetris/highscore.txt", "r");
  if (!file) {
    exit_code = 0;
  } else {
    if (fscanf(file, "%d", high_score) != 1) {
      exit_code = 0;
    }
    fclose(file);
  }
  return exit_code;
}

int saveHighScore(int high_score) {
  int exit_code = 1;
  FILE *file = fopen("brick_game/tetris/highscore.txt", "w");
  if (!file) {
    exit_code = 0;
  } else {
    fprintf(file, "%d\n", high_score);
    fclose(file);
  }
  return exit_code;
}
