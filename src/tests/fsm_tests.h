#ifndef FSM_TESTS_H
#define FSM_TESTS_H

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

#endif