#include <ncurses.h>
#include "backend.h"

void draw_game(GameState *game);

int main() {
    GameState game;
    init_game(&game);

    initscr();            // инициализация ncurses
    noecho();             // не выводить нажатые символы
    cbreak();             // обрабатывать ввод сразу
    keypad(stdscr, TRUE); // стрелки
    nodelay(stdscr, TRUE);// getch не ждёт

    int ch;
    while (1) {
        draw_game(&game);

        ch = getch();
        switch (ch) {
            case KEY_LEFT:  move_left(&game); break;
            case KEY_RIGHT: move_right(&game); break;
            case KEY_DOWN:  move_down(&game); break;
            case 'q': endwin(); return 0; 
        }

        napms(400);
        move_down(&game); 
    }

    endwin(); // завершить работу ncurses
    return 0;
}