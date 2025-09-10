#include "frontend.h"

UserAction_t getUserAction() {
    UserAction_t action = ERR;
    int ch = getch(); 
    switch (ch) {
        case 's': case 'S':   
            action = Start; 
            break;
        case 'p': case 'P':   
            action = Pause;
            break;
        case 'q': case 'Q':   
            action = Terminate;
            break;
        case KEY_LEFT:
            action = Left;
            break;
        case KEY_RIGHT:
            action = Right;
            break;
        case KEY_UP:
            action = Up;  
            break;    
        case KEY_DOWN:
            action = Down;  
            break;  
        case 'r': case 'R':         
            action = Action;
            break; 
            //подуамть над default? Может норм, если какое-то из UserAction_t будет возвращаться если нет нажатия
    }

    return action;
}

void printOverlay(const char *game_name){
    clear();
    mvprintw(6, (FIELD_WIDTH * 2 + 2 - (int)strlen(game_name)) / 2, "%s", game_name);
    mvprintw(9, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press S to start")) / 2, "Press S to start");
    mvprintw(10, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press Q to exit")) / 2, "Press Q to exit");
    
    refresh();
}

void printNextPiece(GameInfo_t *info) {
    int start_x = FIELD_WIDTH * 2 + 4;
    int start_y = 2;

    mvprintw(start_y - 1, start_x, "Next:");

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            mvprintw(start_y + y, start_x + x * 2,
                     info->next[y][x] ? "<>" : "  ");
        }
    }
}

void printField(GameInfo_t *info){
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

        printNextPiece(info);
}

void print_stat(GameInfo_t *info){
    mvprintw(8, FIELD_WIDTH * 2 + 4, "Score: %d", info->score);
    mvprintw(9, FIELD_WIDTH * 2 + 4, "High:  %d", info->high_score);
    mvprintw(10, FIELD_WIDTH * 2 + 4, "Level: %d", info->level);
    mvprintw(11, FIELD_WIDTH * 2 + 4, "Speed: %d", info->speed);
}

void drawGameInfo(GameInfo_t *info) {
    clear();

    printField(info);

    if (info->level == 0) {
        // Баннер START
        mvprintw(6, (FIELD_WIDTH * 2 + 2 - (int)strlen("THE GAME")) / 2, "THE GAME");
        mvprintw(7, (FIELD_WIDTH * 2 + 2 - (int)strlen("is ready to start")) / 2, "is ready to start");
        mvprintw(9, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press S to start")) / 2, "Press S to start");
        mvprintw(10, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press Q to exit")) / 2, "Press Q to exit");
    }else if(info->pause == 1){
        // Баннер Paused
        mvprintw(5, (FIELD_WIDTH * 2 + 2 - (int)strlen("PAUSE")) / 2, "PAUSE");
        mvprintw(7, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press P to continue")) / 2, "Press P to continue");
        mvprintw(9, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press Q to exit")) / 2, "Press Q to exit");
    }else if (info->level == -1) { //лучше проверять на NULL gameInfo поля
        // Баннер GAMEOVER
        mvprintw(5, (FIELD_WIDTH * 2 + 2 - (int)strlen("GAME OVER")) / 2, "GAME OVER");
        mvprintw(7, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press S to play again")) / 2, "Press S to play again");
        mvprintw(9, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press Q to exit")) / 2, "Press Q to exit");   
    } else if (info->high_score == -1) {
        // Баннер FILE_ERROR
        mvprintw(4, (FIELD_WIDTH * 2 + 2 - (int)strlen("ERROR")) / 2, "ERROR");
        mvprintw(5, (FIELD_WIDTH * 2 + 2 - (int)strlen("high score file")) / 2, "high score file");
        mvprintw(6, (FIELD_WIDTH * 2 + 2 - (int)strlen("not found")) / 2, "not found");
        mvprintw(8, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press S")) / 2, "Press S");
        mvprintw(9, (FIELD_WIDTH * 2 + 2 - (int)strlen("to start anyway")) / 2, "to start anyway");
        mvprintw(10, (FIELD_WIDTH * 2 + 2 - (int)strlen("Press Q to exit")) / 2, "Press Q to exit");
    }else{
        mvprintw(17, FIELD_WIDTH * 2 + 4, "KEY RIGHT - Move right");
        mvprintw(18, FIELD_WIDTH * 2 + 4, "KEY LEFT - Move left");
        mvprintw(19, FIELD_WIDTH * 2 + 4, "KEY DOWN - Fall down");
        mvprintw(20, FIELD_WIDTH * 2 + 4, "R - Rotate");
        mvprintw(21, FIELD_WIDTH * 2 + 4, "P - Pause");
        mvprintw(21, FIELD_WIDTH * 2 + 14, "Q - Exit");
    }

    print_stat(info);

    refresh();
}

