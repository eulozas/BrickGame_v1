#ifndef FSM_H
#define FSM_H

#include "backend.h"
#include "../../gui/cli/frontend.h"

typedef enum {
    START = 0,       
    SPAWN,           
    MOVING,          
    SHIFTING,        
    ATTACHING,  
    PAUSE,     
    GAMEOVER,        
    EXIT_STATE,  
    FILE_ERROR_STATE 
} tet_state;

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
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

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
    long last_fall_time;   // когда в последний раз падала фигура
    long fall_delay;       // интервал между падениями (мс)
} GameStruct_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif 