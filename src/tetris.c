#include <ncurses.h>
#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

int main() {
    init_ncurses();        // инициализация ncurses
    initGame();            // инициализация тетриса

    runGame();         // цикл игры (CLI + Tetris)

    stop_ncurses();         // завершение ncurses
    return 0;
}