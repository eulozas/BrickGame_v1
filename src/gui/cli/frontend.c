#include <ncurses.h>
#include "../../brick_game/tetris/backend.h"

void draw_game(GameState *game) {
    clear();

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (game->field[y][x]) {
                mvprintw(y, x * 2, "[]"); 
            } else {
                mvprintw(y, x * 2, " ."); 
            }
        }
    }

    mvprintw(game->y, game->x * 2, "[]");

    refresh();
}