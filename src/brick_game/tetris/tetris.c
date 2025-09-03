#include "tetris.h"

int main() {  
    init_ncurses();
    print_overlay();  
    UserAction_t action;  
    nodelay(stdscr, FALSE);// getch ждёт 
    do {
        action = getUserAction();
    } while (action != Start && action != Terminate);

    if (action == Start) {
        nodelay(stdscr, TRUE);// getch не ждёт 
        game_loop();
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

void game_loop() {

    bool break_flag = TRUE;
    int hold = 0;
    while (break_flag) {
        UserAction_t action = getUserAction();
        userInput(action, hold);//тут меняются состояния автомата и игровая структура
        GameInfo_t snapshot = updateCurrentState(); //делается снимок игровой структуры, копируются некоторые поля в инфо структуру для отрисовки во фронте
        drawGameInfo(&snapshot);
        freeGameInfo(&snapshot);

        if (action == Terminate) break_flag = FALSE;//придумать другой выход из цикла!
        
        napms(200);
    }
}