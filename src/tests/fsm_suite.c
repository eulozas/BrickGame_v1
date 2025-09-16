#include <check.h>
#include "../brick_game/tetris/fsm.h"
#include "fsm_tests.h"
#include "../brick_game/tetris/backend.h"
#include "../brick_game/tetris/pieces.h"

START_TEST(fsm_start1) {
    
    GameStruct_t game;
    restartGameStruct(&game);

    on_start_state(Start, &game);

    ck_assert_int_eq(game.level, 1);
    ck_assert_int_eq(game.speed, 1);
    ck_assert(game.state == SPAWN);
}
END_TEST

START_TEST(fsm_start2) {
    
    GameStruct_t game;
    restartGameStruct(&game);

    on_start_state(Terminate, &game);

    ck_assert_int_eq(game.level, 0);
    ck_assert_int_eq(game.speed, 0);
    ck_assert(game.state == EXIT_STATE);
}
END_TEST

START_TEST(fsm_start3) {
    
    GameStruct_t game;
    restartGameStruct(&game);

    on_start_state(Pause, &game);

    ck_assert_int_eq(game.level, 0);
    ck_assert_int_eq(game.speed, 0);
    ck_assert(game.state == START);
}
END_TEST

START_TEST(fsm_start4) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.high_score = -1;
    on_start_state(Start, &game);
    ck_assert_int_eq(game.level, 1);
    ck_assert_int_eq(game.speed, 1);
    ck_assert(game.state == FILE_ERROR_STATE);
}
END_TEST


START_TEST(fsm_spawn1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = SPAWN;
    on_spawn_state(&game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_spawn2) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = SPAWN;
    memcpy(game.next, tetrominos[2], sizeof(game.next));
    game.field[0][4] = 1;
    game.field[0][5] = 1;
    game.field[0][6] = 1;
    game.field[0][7] = 1;
    on_spawn_state(&game);
    ck_assert(game.state == GAMEOVER);
}
END_TEST

START_TEST(fsm_moving1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(Up, &game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_moving2) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.currentPiece[0][0] = 1;
    game.currentX = 0;
    game.currentY = FIELD_HEIGHT - 2;
    on_moving_state(Down, &game);
    ck_assert(game.state == ATTACHING);
}
END_TEST

START_TEST(fsm_moving3) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(Right, &game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_moving4) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(Left, &game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_moving5) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.fall_delay = 500;
    game.last_fall_time = getCurrentTimeMs() - 1000;
    on_moving_state(Up, &game);
    ck_assert(game.state == SHIFTING);
}
END_TEST

START_TEST(fsm_moving6) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(Action, &game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_moving7) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(Terminate, &game);
    ck_assert(game.state == EXIT_STATE);
}
END_TEST

START_TEST(fsm_moving8) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(Pause, &game);
    ck_assert_int_eq(game.pause, 1);
    ck_assert(game.state == PAUSE);
}
END_TEST

START_TEST(fsm_moving9) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = MOVING;
    game.last_fall_time = getCurrentTimeMs();
    game.fall_delay = 1000;
    on_moving_state(-1, &game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_shifting1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = SHIFTING;
    on_shifting_state(&game);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_shifting2) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = SHIFTING;
    game.currentPiece[0][0] = 1;
    game.field[1][0] = 1;
    on_shifting_state(&game);
    ck_assert(game.state == ATTACHING);
}
END_TEST

START_TEST(fsm_attaching1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = SHIFTING;
    on_attaching_state(&game);
    ck_assert(game.state == SPAWN);
}
END_TEST

START_TEST(fsm_pause1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = PAUSE;
    on_pause_state(Pause, &game);
    ck_assert_int_eq(game.pause, 0);
    ck_assert(game.state == MOVING);
}
END_TEST

START_TEST(fsm_pause2) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = PAUSE;
    on_pause_state(Terminate, &game);
    ck_assert(game.state == EXIT_STATE);
}
END_TEST

START_TEST(fsm_pause3) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = PAUSE;
    on_pause_state(Left, &game);
    ck_assert(game.state == PAUSE);
}
END_TEST

START_TEST(fsm_gameover1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = GAMEOVER;
    on_gameover_state(Start, &game);
    ck_assert(game.state == START);
}
END_TEST

START_TEST(fsm_gameover2) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = GAMEOVER;
    on_gameover_state(Terminate, &game);
    ck_assert(game.state == EXIT_STATE);
}
END_TEST

START_TEST(fsm_gameover3) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = GAMEOVER;
    on_gameover_state(-1, &game);
    ck_assert(game.state == GAMEOVER);
}
END_TEST

START_TEST(fsm_exit1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = EXIT_STATE;
    on_exit_state(&game);
    ck_assert_int_eq(game.running, 0);
}
END_TEST

START_TEST(fsm_file_error1) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = FILE_ERROR_STATE;
    on_file_error_state(Start, &game);
    ck_assert_int_eq(game.high_score, -1);
    ck_assert(game.state == SPAWN);
}
END_TEST

START_TEST(fsm_file_error2) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = FILE_ERROR_STATE;
    on_file_error_state(Terminate, &game);
    ck_assert(game.state == EXIT_STATE);
}
END_TEST

START_TEST(fsm_file_error3) {
    GameStruct_t game;
    restartGameStruct(&game);
    game.state = FILE_ERROR_STATE;
    on_file_error_state(Up, &game);
    ck_assert(game.state == FILE_ERROR_STATE);
}
END_TEST


START_TEST(fsm_user_input1) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = START;
    userInput(Start, false);
    ck_assert_int_eq(game->state, SPAWN);
}
END_TEST

START_TEST(fsm_user_input2) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = SPAWN;
    userInput(-1, false);
    ck_assert_int_eq(game->state, MOVING);
}
END_TEST

START_TEST(fsm_user_input3) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = MOVING;
    userInput(Terminate, false);
    ck_assert_int_eq(game->state, EXIT_STATE);
}
END_TEST

START_TEST(fsm_user_input4) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = SHIFTING;
    userInput(-1, false);
    ck_assert_int_eq(game->state, MOVING);
}
END_TEST

START_TEST(fsm_user_input5) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = ATTACHING;
    userInput(-1, false);
    ck_assert_int_eq(game->state, SPAWN);
}
END_TEST

START_TEST(fsm_user_input6) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = PAUSE;
    userInput(Pause, false);
    ck_assert_int_eq(game->state, MOVING);
}
END_TEST

START_TEST(fsm_user_input7) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = GAMEOVER;
    userInput(Start, false);
    ck_assert_int_eq(game->state, START);
}
END_TEST

START_TEST(fsm_user_input8) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = FILE_ERROR_STATE;
    userInput(Start, false);
    ck_assert_int_eq(game->state, SPAWN);
}
END_TEST

START_TEST(fsm_user_input9) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = EXIT_STATE;
    userInput(-1, false);
}
END_TEST

START_TEST(fsm_user_input10) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = START;
    userInput(Start, true);
    ck_assert_int_eq(game->state, START);
}
END_TEST

START_TEST(fsm_user_input11) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    game->state = 123; 
    userInput(Start, false);
    ck_assert_int_eq(game->state, 123);
}
END_TEST

START_TEST(fsm_upd_current_state1) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    GameInfo_t snapshot = updateCurrentState(); 
    ck_assert_int_eq(game->state, START);
    freeGameInfo(&snapshot);
}
END_TEST

START_TEST(fsm_upd_current_state2) {
    GameStruct_t *game = getGameStruct();
    restartGameStruct(game);
    GameInfo_t snapshot = updateCurrentState(); 
    ck_assert_int_eq(game->state, START);
    game->running = 0;
    snapshot = updateCurrentState(); 
    ck_assert_ptr_null(snapshot.field);
}
END_TEST

Suite *fsm_suite() {
  Suite *s = suite_create("fsm_suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, fsm_start1);
  tcase_add_test(tc, fsm_start2);
  tcase_add_test(tc, fsm_start3);
  tcase_add_test(tc, fsm_start4);
  tcase_add_test(tc, fsm_spawn1);
  tcase_add_test(tc, fsm_spawn2);
  tcase_add_test(tc, fsm_moving1);
  tcase_add_test(tc, fsm_moving2);
  tcase_add_test(tc, fsm_moving3);
  tcase_add_test(tc, fsm_moving4);
  tcase_add_test(tc, fsm_moving5);
  tcase_add_test(tc, fsm_moving6);
  tcase_add_test(tc, fsm_moving7);
  tcase_add_test(tc, fsm_moving8);
  tcase_add_test(tc, fsm_moving9);
  tcase_add_test(tc, fsm_shifting1);
  tcase_add_test(tc, fsm_shifting2);
  tcase_add_test(tc, fsm_attaching1);
  tcase_add_test(tc, fsm_pause1);
  tcase_add_test(tc, fsm_pause2);
  tcase_add_test(tc, fsm_pause3);
  tcase_add_test(tc, fsm_gameover1);
  tcase_add_test(tc, fsm_gameover2);
  tcase_add_test(tc, fsm_gameover3);
  tcase_add_test(tc, fsm_exit1);
  tcase_add_test(tc, fsm_file_error1);
  tcase_add_test(tc, fsm_file_error2);
  tcase_add_test(tc, fsm_file_error3);
  tcase_add_test(tc, fsm_user_input1);
  tcase_add_test(tc, fsm_user_input2);
  tcase_add_test(tc, fsm_user_input3);
  tcase_add_test(tc, fsm_user_input4);
  tcase_add_test(tc, fsm_user_input5);
  tcase_add_test(tc, fsm_user_input6);
  tcase_add_test(tc, fsm_user_input7);
  tcase_add_test(tc, fsm_user_input8);
  tcase_add_test(tc, fsm_user_input9);
  tcase_add_test(tc, fsm_user_input10);
  tcase_add_test(tc, fsm_user_input11);
  tcase_add_test(tc, fsm_upd_current_state1);
  tcase_add_test(tc, fsm_upd_current_state2);

  suite_add_tcase(s, tc);
  return s;
}