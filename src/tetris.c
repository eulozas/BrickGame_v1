#include "tetris.h"

int main() {  
    
    init_ncurses();
    print_overlay();          // стартовый экран (баннер)
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
    state_t current_state = START;
    GameInfo_t info = {0};

    initGame();

    while (current_state != EXIT_STATE) {
        int ch = getch();
        if (ch != ERR) { // есть ввод
            switch (ch) {
                case 'q': userInput(Terminate, false); break;
                case 's': userInput(Start, false); break;
                case 'p': userInput(Pause, false); break;
                case 'r': userInput(Action, false); break;
                case KEY_LEFT:  userInput(Left, false); break;
                case KEY_RIGHT: userInput(Right, false); break;
                case KEY_UP:    userInput(Up, false); break;
                case KEY_DOWN:  userInput(Down, false); break;
            }
        }

        info = updateCurrentState();       
        current_state = getCurrentState();
        draw_game(&info, current_state);

        napms(50);
    }
}