#ifndef HELPERS_H
#define HELPERS_H

#include "backend.h"

void spawn_new_piece(GameState *game);
void move_piece_down(GameState *game);
int canMoveLeft(GameState *game);
void moveLeft(GameState *game);
void rotate_piece(GameState *game);

#endif