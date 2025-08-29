#include "backend.h"
#include "helpers.h"
#include "state.h"
#include <stdlib.h>
#include <string.h>

static state_t current_state = START;
static GameState game;  // глобальное внутреннее состояние

void initGame() {
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            game.field[y][x] = 0;
        }
    }

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            game.next[y][x] = 0;
            game.currentPiece[y][x] = 0;
        }
    }
    game.currentX = FIELD_WIDTH/2;
    game.currentY = 0;
    game.score = 0;
    game.high_score = 0;
    game.level = 1;
    game.speed = 1;
    game.pause = 0;
    game.running = 1;
}

state_t getCurrentState() {
    return current_state;
}


void userInput(UserAction_t action, bool hold) {
    switch(action) {

        case Start:
        if (current_state == START || current_state == GAMEOVER)
        current_state = SPAWN;
        break;

        case Pause:
        if(current_state == MOVING){
            current_state = PAUSE;
        }else{
            current_state = MOVING;
        } 
        break;

        case Left:
         if (current_state == MOVING && canMoveLeft(&game)) {
            moveLeft(&game);
            current_state = SHIFTING;
         }
        break;

        case Right:
        break;

        case Up:
        break;

        case Down:
        break;

        case Action:
        if (current_state == MOVING) {
            rotate_piece(&game);  
            current_state = SHIFTING;
        }
        break;

        case Terminate:
        current_state = EXIT_STATE;
        break;
    }
}

GameInfo_t copy_game_info(GameState *game) {
    GameInfo_t info;
    info.field = malloc(FIELD_HEIGHT * sizeof(int *));
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        info.field[y] = malloc(FIELD_WIDTH * sizeof(int));
        memcpy(info.field[y], game->field[y], FIELD_WIDTH * sizeof(int));
    }

    info.next = malloc(FIELD_HEIGHT * sizeof(int *));
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        info.next[y] = malloc(FIELD_WIDTH * sizeof(int));
        memcpy(info.next[y], game->next[y], FIELD_WIDTH * sizeof(int));
    }

    info.score = game->score;
    info.high_score = game->high_score;
    info.level = game->level;
    info.speed = game->speed;
    info.pause = game->pause;

    return info;
}

GameInfo_t updateCurrentState() {
    if (current_state != EXIT_STATE) {//+file_error_state later
        switch(current_state) {
            case START://в этом статусе игра просто инициализирована
                break;
            case SPAWN:
                spawn_new_piece(&game);
                current_state = MOVING;
                break;
            case MOVING:
                move_piece_down(&game); // падение
            break;
            case SHIFTING:
                // обрабатываем userInput(Left/Right/Up/Down)
                current_state = MOVING;
                break;
            case ATTACHING:
                //fix_piece_to_field(&game);
                //clear_full_lines(&game);
                    // if (check_game_over(&game))
                        // current_state = GAMEOVER;
                    // else
                         // current_state = SPAWN;
                //  break;
             case GAMEOVER:
                // выводим сообщение, ждём Start или Exit
                break;
            case EXIT_STATE:
                break;
            case PAUSE:
                break;
        }
    }
    return copy_game_info(&game); 
}

static void freeMatrix(int **m, int h) {
    if (!m) return;
    for (int i = 0; i < h; i++) {
        free(m[i]);
    }
    free(m);
}

void freeGameInfo(GameInfo_t *info) {
    if (!info) return;
    freeMatrix(info->field, FIELD_HEIGHT);
    freeMatrix(info->next, 4);
    info->field = NULL;
    info->next = NULL;
}