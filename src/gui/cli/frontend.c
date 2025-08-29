#include "frontend.h"

void print_overlay(){
    print_center(FIELD_HEIGHT/2 - 1, "TETRIS");
}

void print_center(int row, const char *msg) {
    int col = (FIELD_WIDTH * 2 + 2 - (int)strlen(msg)) / 2;
    mvprintw(row, col, "%s", msg);
}

void draw_game(GameInfo_t *state, state_t current_state) {
    clear();

    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(0, x, "#");

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        mvprintw(y + 1, 0, "#"); 
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (current_state == START || current_state == GAMEOVER) {
                mvprintw(y + 1, x * 2 + 1, "  "); 
            } else {
                mvprintw(y + 1, x * 2 + 1,
                         state->field[y][x] ? "<>" : "  ");
            }
        }
        mvprintw(y + 1, FIELD_WIDTH * 2 + 1, "#"); 
    }

    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(FIELD_HEIGHT + 1, x, "#");

    mvprintw(2, FIELD_WIDTH * 2 + 4, "Score: %d", state->score);
    mvprintw(3, FIELD_WIDTH * 2 + 4, "Level: %d", state->level);

     if (current_state == MOVING){
        print_center(FIELD_HEIGHT/2 - 1, "MOVING");
     }

    if (current_state == START) {
        print_center(FIELD_HEIGHT/2 - 1, "Press S to Start");
        print_center(FIELD_HEIGHT/2,     "Press Q to Quit");
    } else if (current_state == PAUSE) {
        print_center(FIELD_HEIGHT/2, "PAUSED");
        print_center(FIELD_HEIGHT/2 + 1, "Press P to continue");
    } else if (current_state == GAMEOVER) {
        print_center(FIELD_HEIGHT/2 - 1, "GAME OVER");
        print_center(FIELD_HEIGHT/2,     "Press S to Restart");
        print_center(FIELD_HEIGHT/2 + 1, "Press Q to Exit");
    }

    refresh();
}

