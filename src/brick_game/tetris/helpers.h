#ifndef HELPERS_H
#define HELPERS_H

#include "backend.h"

void spawn_new_piece(GameStruct_t *game);
void move_piece_down(GameStruct_t *game);
int canMoveLeft(GameStruct_t *game);
void moveLeft(GameStruct_t *game);
int canMoveRight(GameStruct_t *game);
void moveRight(GameStruct_t *game);
void rotate_piece(GameStruct_t *game);

#endif