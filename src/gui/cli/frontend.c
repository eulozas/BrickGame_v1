#include <ncurses.h>
#include "frontend.h"
#include "../../brick_game/tetris/backend.h"

void init_ncurses() {
    initscr();            // инициализация ncurses
    noecho();             // не выводить нажатые символы
    //cbreak();             // обрабатывать ввод сразу  ?????????????
    curs_set(FALSE); //?????????
    keypad(stdscr, TRUE); // стрелки
    nodelay(stdscr, TRUE);// getch не ждёт
}

void stop_ncurses() {
    endwin();
}

void draw_game(GameInfo_t *state) {
    clear();
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (state->field[y][x])
                mvprintw(y, x * 2, "[]");
            else
                mvprintw(y, x * 2, " .");
        }
    }
    mvprintw(0, FIELD_WIDTH * 2 + 2, "Score: %d", state->score);
    refresh();
}

void runGame() {
    bool running = true;
    bool started = false;

    // пока игра не началась — рисуем стартовый экран
    while (running) {
        int ch = getch();

        if (!started) {
            // ждём кнопку "Start"
            if (ch == 's') { // например, 's' = Start
                userInput(Start, false);  // сообщаем в библиотеку
                started = true;
            } else if (ch == 'q') { // выход из игры
                running = false;
            }

            clear();
            mvprintw(10, 5, "Press S to Start, Q to Quit");
            refresh();
        } 
        else {
            // игра уже началась — обычная логика
            switch (ch) {
                case KEY_LEFT:  userInput(Left, false); break;
                case KEY_RIGHT: userInput(Right, false); break;
                case KEY_UP:    userInput(Up, false); break;
                case KEY_DOWN:  userInput(Down, false); break;
                case ' ':       userInput(Action, false); break;
                case 'p':       userInput(Pause, false); break;
                case 'q':       userInput(Terminate, false); running = false; break;
            }

            // обновляем состояние
            GameInfo_t info = updateCurrentState();
            draw_game(&info);
            freeGameInfo(&info);

            napms(200);
        }
    }
}
