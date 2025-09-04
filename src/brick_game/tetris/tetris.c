#include "tetris.h"

int main() {  
    init_ncurses();
    printOverlay("TETRIS"); 
    UserAction_t action;  
    nodelay(stdscr, FALSE);// getch ждёт 
    do {
        action = getUserAction();
    } while (action != Start && action != Terminate);

    if (action == Start) {
        nodelay(stdscr, TRUE);// getch не ждёт 
        gameLoop();
    }
    endwin();
    return 0;
}

void init_ncurses() {
    initscr();            // инициализация ncurses
    noecho();             // не выводить нажатые символы
    cbreak();             // не ждать enter при вводе
    curs_set(FALSE); // не видеть курсор
    keypad(stdscr, TRUE); // стрелки
}

void gameLoop() {

    bool break_flag = TRUE;
    int hold = 0;

    while (break_flag) {
        UserAction_t action = getUserAction();
        //тут создается впервые статик структура игры и меняются состояния автомата и игровая структура
        userInput(action, hold);
        //тут создается впервые статик структура инфоигры, туда копируются некоторые поля в инфо структуру для отрисовки во фронте
        GameInfo_t snapshot = updateCurrentState(); 
        if (snapshot.field){ 
            drawGameInfo(&snapshot);
        }else{
            break_flag = FALSE;
        }
        napms(200);
    }
}