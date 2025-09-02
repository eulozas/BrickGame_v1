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
} GameInfo_t; //может вынести в отдельный хедер???

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif 