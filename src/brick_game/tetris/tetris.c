#include "tetris.h"

int main() {  
    init_ncurses();
    print_overlay();          // стартовый экран (баннер) Убрать??
    game_loop(); 
    endwin();
    return 0;
}

void init_ncurses() {
    initscr();            // инициализация ncurses
    noecho();             // не выводить нажатые символы
    cbreak();             // не ждать enter при вводе
    curs_set(FALSE); // не видеть курсор
    keypad(stdscr, TRUE); // стрелки
    nodelay(stdscr, TRUE);// getch не ждёт
}

void game_loop() {

    bool break_flag = TRUE;
    int hold = 0;
    while (break_flag) {
        UserAction_t action = getUserAction();
        userInput(action, hold);//тут меняются состояния автомата и игровая структура
        GameInfo_t snapshot = updateCurrentState(); //делается снимок игровой структуры, копируются некоторые поля в инфо структуру для отрисовки во фронте
        drawGame(snapshot);
        free_game_info(&snapshot);

        if (snapshot.pause && snapshot.level == -1) break_flag = FALSE; //тут подумать условия выхода из цикла
        napms(50);
    }
}