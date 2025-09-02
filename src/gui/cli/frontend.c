#include "frontend.h"

UserAction_t getUserAction() {
    int ch = getch(); 
    switch (ch) {
        case KEY_LEFT:
            return Left;
        case KEY_RIGHT:
            return Right;
        case KEY_UP:
            return Up;      
        case KEY_DOWN:
            return Down;    
        case 'r': case 'R':         
            return Action;
        case 'p': case 'P':   
            return Pause;
        case 'q': case 'Q':   
            return Terminate;
        case 's': case 'S':   
            return Start; 
    }
}

void print_center(int row, const char *msg) {
    int col = (FIELD_WIDTH * 2 + 2 - (int)strlen(msg)) / 2;
    mvprintw(row, col, "%s", msg);
}

void print_overlay(){
    clear();
    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(0, x, "-");
    
    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(0, x, "-");

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        mvprintw(y + 1, 0, "|"); 
        for (int x = 0; x < FIELD_WIDTH; x++) {
            mvprintw(y + 1, x * 2 + 1,
            "  ");
            
        }
        mvprintw(y + 1, FIELD_WIDTH * 2 + 1, "|"); 
    }

    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(FIELD_HEIGHT + 1, x, "-");

    mvprintw(2, FIELD_WIDTH * 2 + 4, "Score: %d", 0);
    mvprintw(3, FIELD_WIDTH * 2 + 4, "Level: %d", 0);


    mvprintw(2, FIELD_WIDTH * 2 + 4, "Score: %d", 0);

    mvprintw(5, (FIELD_WIDTH * 2 + 2 - (int)strlen("TETRIS")) / 2, "TETRIS");
    mvprintw(8, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press Q to Quite")) / 2, "Press Q to Quite");
    mvprintw(10, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press S to Start")) / 2, "Press S to Start");
   
}

void drawGameInfo(GameInfo_t *info) {
    clear();

    if (info->level == -1) {//лучше проверять на NULL gameInfo поля
        // Баннер Game Over
        mvprintw(LINES/2 - 1, (COLS - 9) / 2, "GAME OVER");
        mvprintw(LINES/2 + 1, (COLS - 27) / 2, "Press S to play again");
        mvprintw(LINES/2 + 2, (COLS - 27) / 2, "Press Q to exit");
    } else if (info->pause) {
        // Баннер Paused
        mvprintw(LINES/2, (COLS - 5) / 2, "PAUSE");
    } else {

    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(0, x, "#");

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        mvprintw(y + 1, 0, "#"); 
        for (int x = 0; x < FIELD_WIDTH; x++) {
            mvprintw(y + 1, x * 2 + 1,
            info->field[y][x] ? "<>" : "  ");
            
        }
        mvprintw(y + 1, FIELD_WIDTH * 2 + 1, "#"); 
    }

    for (int x = 0; x < FIELD_WIDTH * 2 + 2; x++)
        mvprintw(FIELD_HEIGHT + 1, x, "#");

    mvprintw(10, FIELD_WIDTH * 2 + 4, "Score: %d", info->score);
    mvprintw(11, FIELD_WIDTH * 2 + 4, "High:  %d", info->high_score);
    mvprintw(12, FIELD_WIDTH * 2 + 4, "Level: %d", info->level);
    mvprintw(13, FIELD_WIDTH * 2 + 4, "Speed: %d", info->speed);
}

    refresh();
}

