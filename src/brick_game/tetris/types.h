#ifndef TYPES_H
#define TYPES_H

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

#endif