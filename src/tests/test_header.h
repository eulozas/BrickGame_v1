#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include "../brick_game/tetris/backend.h"
#include "../brick_game/tetris/types.h"

// Прототипы внутренних функций для тестов
void on_start_state(UserAction_t action, GameStruct_t *game);
void on_spawn_state(GameStruct_t *game);
void on_moving_state(UserAction_t action, GameStruct_t *game);
void on_shifting_state(GameStruct_t *game);
void on_attaching_state(GameStruct_t *game);
void on_pause_state(UserAction_t action, GameStruct_t *game);
void on_gameover_state(UserAction_t action, GameStruct_t *game);
void on_exit_state(GameStruct_t *game);
void on_file_error_state(UserAction_t action, GameStruct_t *game);

void draw_piece_to_field(GameStruct_t *game);
void clear_piece_from_field(GameStruct_t *game);
int canMoveRight(GameStruct_t *game);
int canMoveLeft(GameStruct_t *game);
int canRotate(GameStruct_t *game, int rotated[4][4], int offsetX, int offsetY);
int clearLines(GameStruct_t *game);
void updateScore(GameStruct_t *game, int lines_cleared);
void updateLevel(GameStruct_t *game);
void updateHighScore(GameStruct_t *game);

#endif