#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>

#define HIGHSCORE_FILE "brick_game/tetris/highscore.txt"

int loadHighScore(int *high_score);
int saveHighScore(int high_score);

#endif