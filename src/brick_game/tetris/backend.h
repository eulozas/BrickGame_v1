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

// внутренняя структура
typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    int next[4][4];  // next-фигура
    int currentPiece[4][4]; // текущая фигура
    int currentX, currentY;  
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    int running;
} GameState;

void initGame();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void freeGameInfo(GameInfo_t *info);

#endif