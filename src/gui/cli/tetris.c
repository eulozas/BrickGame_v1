#include <stdbool.h>
#include "../../brick_game/tetris/fsm.h"
#include "frontend.h"


void gameLoop() {

    bool break_flag = true;
    bool hold = false;

    while (break_flag) {
        UserAction_t action = getUserAction();
        //тут создается впервые статик структура игры и меняются состояния автомата и игровая структура
        userInput(action, hold);
        //тут создается впервые статик структура инфоигры, туда копируются некоторые поля в инфо структуру для отрисовки во фронте
        GameInfo_t snapshot = updateCurrentState(); 
        if (snapshot.field){ 
            drawGameInfo(&snapshot);
        }else{
            break_flag = false;
        }
        delay_ncurses(20);
    }
}

int main() {  
    init_ncurses();
    printOverlay("TETRIS"); 
    UserAction_t action;  
    block_input_ncurses();// getch ждёт 
    do {
        action = getUserAction();
    } while (action != Start && action != Terminate);

    if (action == Start) {
        noblock_input_ncurses();// getch не ждёт 
        gameLoop();
    }
    end_ncurses();
    return 0;
}



