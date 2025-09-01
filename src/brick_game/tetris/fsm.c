#include "fsm.h"

UserAction_t getUserAction() {
    int ch = getch(); 
    switch (ch) {
        case KEY_LEFT:
            return Left;
        case KEY_RIGHT:
            return Right;
        case KEY_UP:
            return Up;      
        case KEY_DOWN:
            return Down;    
        case 'r':          
            return Action;
        case 'p': case 'P':   
            return Pause;
        case 'q': case 'Q':   
            return Terminate;
        default:
            return Start;  
    }
}

void userInput(UserAction_t action, bool hold) {
    GameStruct_t *game = getGameState();
    switch(action) {
        case Left:
        //moveLeft(game);
        break;
        case Right:
        //moveRight(game);
        break;
        case Down:
        //moveDown(game);
        break;
        case Up:
        //rotatePiece(game);
        break;
        case Action:
        //dropPiece(game);
        break;
        case Pause:
        //togglePause(game);
        break;
        case Terminate:
        //terminateGame(game);
        break;
        case Start:
        //startGame(game);
        break;
        default:
        break;
    }

    //+логика для hold
}

GameInfo_t updateCurrentState() {
  GameStruct_t *game = getGameState();

    GameInfo_t info;
    info.field = alloc_and_copy_field(game->field);
    info.next = alloc_and_copy_next(game->next);

    info.score = game->score;
    info.high_score = game->high_score;
    info.level = game->level;
    info.speed = game->speed;
    info.pause = game->pause;

    return info;
}
