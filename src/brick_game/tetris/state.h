#ifndef STATE_H
#define STATE_H

typedef enum
{
    START = 0,       
    SPAWN,           
    MOVING,          
   // SHIFTING,        
    ATTACHING,  
    PAUSE,     
    GAMEOVER,        
    EXIT_STATE  
   // FILE_ERROR_STATE 
} state_t;

#endif // STATE_H