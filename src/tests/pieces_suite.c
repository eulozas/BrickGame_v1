#include <check.h>

#include "../brick_game/tetris/backend.h"
#include "../brick_game/tetris/pieces.h"
#include "test_header.h"

START_TEST(pieces_draw_field1) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = 3;
  game.currentY = 5;
  for (int y = 0; y < FIELD_HEIGHT; y++)
    for (int x = 0; x < FIELD_WIDTH; x++) ck_assert_int_eq(game.field[y][x], 0);

  draw_piece_to_field(&game);
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int fx = game.currentX + x;
      int fy = game.currentY + y;
      if (game.currentPiece[y][x]) {
        ck_assert_int_eq(game.field[fy][fx], 2);
      }
    }
  }
}
END_TEST

START_TEST(pieces_draw_field2) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[0], sizeof(game.currentPiece));
  game.currentX = -2;
  game.currentY = FIELD_HEIGHT - 1;
  draw_piece_to_field(&game);
  for (int y = 0; y < FIELD_HEIGHT; y++)
    for (int x = 0; x < FIELD_WIDTH; x++)
      ck_assert(game.field[y][x] == 0 || game.field[y][x] == 2);
}
END_TEST

START_TEST(pieces_clear_field1) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = 3;
  game.currentY = 5;
  draw_piece_to_field(&game);
  clear_piece_from_field(&game);
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int fx = game.currentX + x;
      int fy = game.currentY + y;
      if (game.currentPiece[y][x]) {
        ck_assert_int_eq(game.field[fy][fx], 0);
      }
    }
  }
}
END_TEST

START_TEST(pieces_clear_field2) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[0], sizeof(game.currentPiece));
  game.currentX = -2;
  game.currentY = FIELD_HEIGHT - 1;
  draw_piece_to_field(&game);
  clear_piece_from_field(&game);
  for (int y = 0; y < FIELD_HEIGHT; y++)
    for (int x = 0; x < FIELD_WIDTH; x++) ck_assert_int_eq(game.field[y][x], 0);
}
END_TEST

START_TEST(pieces_move_left) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  moveLeft(&game);
  int res = canMoveLeft(&game);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(pieces_move_left_free) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;
  game.currentY = 0;
  int res = canMoveLeft(&game);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(pieces_move_left_border) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = 0;
  game.currentY = 0;
  int res = canMoveLeft(&game);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(pieces_move_left_blocked) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;
  game.currentY = 0;
  game.field[game.currentY + 1][game.currentX - 1] = 1;

  int res = canMoveLeft(&game);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(pieces_move_right) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH;
  moveRight(&game);
  int res = canMoveRight(&game);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(pieces_move_right_free) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;

  ck_assert_int_eq(canMoveRight(&game), 1);
}
END_TEST

START_TEST(pieces_move_right_border) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH - 3;

  ck_assert_int_eq(canMoveRight(&game), 0);
}
END_TEST

START_TEST(pieces_move_right_blocked) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;
  game.currentY = 1;
  game.field[game.currentY + 1][game.currentX + 3] = 1;
  ck_assert_int_eq(canMoveRight(&game), 0);
}
END_TEST

START_TEST(pieces_move_down_free) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;
  game.currentY = 0;
  ck_assert_int_eq(canMoveDown(&game), 1);
}
END_TEST

START_TEST(pieces_move_down_border) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;
  game.currentY = FIELD_HEIGHT - 2;
  ck_assert_int_eq(canMoveDown(&game), 0);
}
END_TEST

START_TEST(pieces_move_down_blocked) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH / 2;
  game.currentY = 0;
  game.field[2][game.currentX + 1] = 1;
  ck_assert_int_eq(canMoveDown(&game), 0);
}
END_TEST

START_TEST(pieces_attach_ok) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[2], sizeof(game.currentPiece));
  game.currentX = 4;
  game.currentY = 0;
  attachPiece(&game);
  ck_assert_int_eq(game.field[1][4], 1);
  ck_assert_int_eq(game.field[1][5], 1);
  ck_assert_int_eq(game.field[1][6], 1);
  ck_assert_int_eq(game.field[2][5], 1);
}
END_TEST

START_TEST(pieces_attach_negY) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[0], sizeof(game.currentPiece));
  game.currentX = 3;
  game.currentY = -2;
  attachPiece(&game);
  for (int x = 0; x < FIELD_WIDTH; x++) {
    ck_assert_int_eq(game.field[0][x], 0);
  }
}
END_TEST

START_TEST(pieces_attach_out) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[1], sizeof(game.currentPiece));
  game.currentX = FIELD_WIDTH - 1;
  game.currentY = FIELD_HEIGHT - 1;
  attachPiece(&game);
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      ck_assert((game.field[y][x] == 0) || (game.field[y][x] == 1));
    }
  }
}
END_TEST

START_TEST(pieces_rotate_ok) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[0], sizeof(game.currentPiece));
  int before[4][4];
  memcpy(before, game.currentPiece, sizeof(before));
  rotatePiece(&game);
  ck_assert_int_ne(memcmp(before, game.currentPiece, sizeof(before)), 0);
}
END_TEST

START_TEST(pieces_rotate_collision) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[0], sizeof(game.currentPiece));
  game.currentX = 0;
  rotatePiece(&game);
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int fx = game.currentX + x;
      ck_assert(fx >= 0 && fx < FIELD_WIDTH);
    }
  }
}
END_TEST

START_TEST(pieces_rotate_neg) {
  GameStruct_t game;
  restartGameStruct(&game);
  memcpy(game.currentPiece, tetrominos[0],
         sizeof(game.currentPiece));  // I-piece
  int fy = game.currentY + 1;
  for (int x = 0; x < FIELD_WIDTH; x++) {
    game.field[fy][x] = 1;
  }
  int before[4][4];
  memcpy(before, game.currentPiece, sizeof(before));
  rotatePiece(&game);
  ck_assert_int_eq(memcmp(before, game.currentPiece, sizeof(before)), 0);
}
END_TEST

START_TEST(pieces_clear_lines1) {
  GameStruct_t game;
  restartGameStruct(&game);
  for (int x = 0; x < FIELD_WIDTH; x++) game.field[0][x] = 1;
  int cleared = clearLines(&game);
  ck_assert_int_eq(cleared, 1);
  for (int x = 0; x < FIELD_WIDTH; x++) ck_assert_int_eq(game.field[0][x], 0);
  cleared = clearLines(&game);
  ck_assert_int_eq(cleared, 0);
}
END_TEST

START_TEST(pieces_clear_lines2) {
  GameStruct_t game;
  restartGameStruct(&game);
  for (int x = 0; x < FIELD_WIDTH; x++) {
    game.field[19][x] = 1;
    game.field[18][x] = 1;
  }
  for (int y = 0; y < 18; y++)
    for (int x = 0; x < FIELD_WIDTH; x++) game.field[y][x] = 0;

  int cleared = clearLines(&game);
  ck_assert_int_eq(cleared, 2);
  for (int x = 0; x < FIELD_WIDTH; x++) {
    ck_assert_int_eq(game.field[19][x], 0);
    ck_assert_int_eq(game.field[18][x], 0);
  }
}
END_TEST

START_TEST(pieces_update_score) {
  GameStruct_t game;
  restartGameStruct(&game);
  game.score = 0;
  updateScore(&game, 1);
  ck_assert_int_eq(game.score, 100);
  updateScore(&game, 2);
  ck_assert_int_eq(game.score, 100 + 300);
  updateScore(&game, 3);
  ck_assert_int_eq(game.score, 100 + 300 + 700);
  updateScore(&game, 4);
  ck_assert_int_eq(game.score, 100 + 300 + 700 + 1500);
  updateScore(&game, 5);
  ck_assert_int_eq(game.score, 100 + 300 + 700 + 1500);
}
END_TEST

START_TEST(pieces_update_level) {
  GameStruct_t game;
  restartGameStruct(&game);
  game.score = 0;
  game.level = 0;
  updateLevel(&game);
  ck_assert_int_eq(game.level, 1);
  game.score = 1200;
  updateLevel(&game);
  ck_assert_int_eq(game.level, 3);
  ck_assert_int_eq(game.fall_delay, FALL_DELAY - 3 * 100);
  game.score = 10000;
  updateLevel(&game);
  ck_assert_int_eq(game.level, 10);
  ck_assert_int_eq(game.fall_delay >= 100, 1);
}
END_TEST

START_TEST(pieces_update_high_score) {
  GameStruct_t game;
  restartGameStruct(&game);

  game.score = 500;
  game.high_score = 400;
  updateHighScore(&game);
  ck_assert_int_eq(game.high_score, 500);

  game.score = 300;
  updateHighScore(&game);
  ck_assert_int_eq(game.high_score, 500);
}
END_TEST

START_TEST(pieces_process_completed_lines) {
  GameStruct_t game;
  restartGameStruct(&game);
  for (int x = 0; x < FIELD_WIDTH; x++) game.field[0][x] = 1;
  game.score = 0;
  game.level = 0;
  game.high_score = 0;
  processCompletedLines(&game);
  ck_assert_int_eq(game.score, 100);
  ck_assert_int_eq(game.level, 1);
  ck_assert_int_eq(game.high_score, 100);
  for (int x = 0; x < FIELD_WIDTH; x++) ck_assert_int_eq(game.field[0][x], 0);
}
END_TEST

Suite *pieces_suite() {
  Suite *s = suite_create("pieces_suite");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, pieces_draw_field1);
  tcase_add_test(tc, pieces_draw_field2);
  tcase_add_test(tc, pieces_clear_field1);
  tcase_add_test(tc, pieces_clear_field2);
  tcase_add_test(tc, pieces_move_left);
  tcase_add_test(tc, pieces_move_left_free);
  tcase_add_test(tc, pieces_move_left_border);
  tcase_add_test(tc, pieces_move_left_blocked);
  tcase_add_test(tc, pieces_move_right);
  tcase_add_test(tc, pieces_move_right_free);
  tcase_add_test(tc, pieces_move_right_border);
  tcase_add_test(tc, pieces_move_right_blocked);
  tcase_add_test(tc, pieces_move_down_free);
  tcase_add_test(tc, pieces_move_down_border);
  tcase_add_test(tc, pieces_move_down_blocked);
  tcase_add_test(tc, pieces_attach_ok);
  tcase_add_test(tc, pieces_attach_negY);
  tcase_add_test(tc, pieces_attach_out);
  tcase_add_test(tc, pieces_rotate_ok);
  tcase_add_test(tc, pieces_rotate_collision);
  tcase_add_test(tc, pieces_rotate_neg);
  tcase_add_test(tc, pieces_clear_lines1);
  tcase_add_test(tc, pieces_clear_lines2);
  tcase_add_test(tc, pieces_update_score);
  tcase_add_test(tc, pieces_update_level);
  tcase_add_test(tc, pieces_update_high_score);
  tcase_add_test(tc, pieces_process_completed_lines);

  suite_add_tcase(s, tc);
  return s;
}