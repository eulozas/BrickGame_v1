#include <check.h>
#include "../brick_game/tetris/fsm.h"
#include "fsm_tests.h"
#include "../brick_game/tetris/backend.h"

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

Suite *fsm_suite() {
  Suite *s = suite_create("fsm_suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, fsm_start1);
  tcase_add_test(tc, fsm_start2);
  tcase_add_test(tc, fsm_start3);
  tcase_add_test(tc, fsm_start4);

  suite_add_tcase(s, tc);
  return s;
}