#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;   // текущее игровое поле
  int **next;    // следующая фигура (пока можно заглушка 2x2)
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// API библиотеки
void initGame();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void freeGameInfo(GameInfo_t *info);

#endif