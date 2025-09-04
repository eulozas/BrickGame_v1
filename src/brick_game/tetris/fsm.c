#include "fsm.h"


long getCurrentTimeMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000L + tv.tv_usec / 1000L;
}

void on_start_state(UserAction_t action, GameStruct_t *game){
        switch (action)
    {
        case Start:
            game->level = 1;
            game->speed = 1;
            if(game->high_score == -1){
                game->state = FILE_ERROR_STATE;
            }else{
                game->state = SPAWN;
            }
            break;
        case Terminate:
            game->state = EXIT_STATE;
            break;
        default:
            game->state = START;
            break;
    }
}

void on_spawn_state(GameStruct_t *game){
    
    spawn_new_piece(game);
    // if (1){//проверить поместиться ли на поле новая фигура
    //     game->state = GAMEOVER;
    // }
    // else{
        game->state = MOVING;
    //}           
}

void on_moving_state(UserAction_t action, GameStruct_t *game){
    switch (action){
        case Up:
        //moveup(game);
        break;
        case Down:
        //movedown(game);
        break;
        case Right:
        //moveright(game);
        break;
        case Left:
        //moveleft(game);
        break;
        case Pause:
        game->state = PAUSE;
        game->pause = 1;
        break;
        case Terminate:
        game->state = EXIT_STATE;
        break;
        default:
        break;
    }
    
    if (game->state == MOVING) {
        long now = getCurrentTimeMs();
        if (now - game->last_fall_time >= game->fall_delay) {
            game->last_fall_time = now;
            game->state = SHIFTING;
        }
    }  
}

void on_shifting_state(UserAction_t action, GameStruct_t *game) {
    if (1) {//проверить можно ли подвинуть вниз фигуру
        move_piece_down(game);
        game->state = MOVING;
    } else {
        game->state = ATTACHING;
    }
}

void on_attaching_state(UserAction_t action, GameStruct_t *game) {
    if (1) {//проверить можно ли убрать линии
        //removeLine(game);
    } 
        game->state = SPAWN;
}


void on_pause_state(UserAction_t action, GameStruct_t *game){

    switch (action)
    {
        case Pause:
            game->pause = 0;
            game->state = MOVING;
            break;
        case Terminate:
            game->state = EXIT_STATE;
            break;
        default:
            break;
    }
}

void on_gameover_state(UserAction_t action, GameStruct_t *game){

    switch (action)
    {
        case Start:
            restartGameStruct(game);
            break;
        case Terminate:
            game->state = EXIT_STATE;
            break;
        default:
            break;
    }
}


void on_exit_state(GameStruct_t *game){
    game->running = 0;
}

void on_file_error_state(UserAction_t action, GameStruct_t *game){

    switch (action)
    {
        case Start:
            game->state = SPAWN;
            game->high_score = -1;//подумать какое значение оставить
            break;
        case Terminate:
            game->state = EXIT_STATE;
            break;
        default:
            break;
    }
}


void userInput(UserAction_t action, bool hold) {
    GameStruct_t *game = getGameStruct();
    switch (game->state) {
        case START:
        on_start_state(action, game);
        break;

        case SPAWN:
        on_spawn_state(game);
        break;

        case MOVING:
        on_moving_state(action, game);
        break;

        case SHIFTING:
        on_shifting_state(action, game);
        break;

        case ATTACHING:
        on_attaching_state(action, game);
        break;

        case PAUSE:
        on_pause_state(action, game);
        break;

        case GAMEOVER:
        on_gameover_state(action, game);
        break;

        case EXIT_STATE:
        on_exit_state(game);
        break;

        case FILE_ERROR_STATE:
        on_file_error_state(action, game);
        break;

        default: break;
    }

    //+логика для hold
}

GameInfo_t updateCurrentState() {

    static GameInfo_t info;
    static int init_info = 0;

    GameStruct_t *game = getGameStruct();

    if (!init_info) {
        info = mallocGameInfo();
        init_info = 1;
    }
    
    copyGameInfo(game, &info);
    if(game->running == 0){
        freeGameInfo(&info);
    }
    return info;
}
