#include "helpers.h"

int loadHighScore(int *high_score) {
  int exit_code = 1;
  FILE *file = fopen(HIGHSCORE_FILE, "r");
  if (!file) {
    exit_code = 0;
  } else {
    if (fscanf(file, "%d", high_score) != 1) {
      fseek(file, 0, SEEK_END);
      if (ftell(file) == 0) {
        *high_score = 0;
      } else {
        exit_code = 0;
      }
    }
    fclose(file);
  }
  return exit_code;
}

int saveHighScore(int high_score) {
  int exit_code = 1;
  FILE *file = fopen(HIGHSCORE_FILE, "w");
  if (!file) {
    exit_code = 0;
  } else {
    fprintf(file, "%d\n", high_score);
    fclose(file);
  }
  return exit_code;
}