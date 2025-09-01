
#include "helpers.h"

void spawn_new_piece(GameStruct_t *game){
     game->field[game->currentY][game->currentX] = 1;
    //нужно сгенерить новую фигуру для некст, а некст перенести в текущую
}


void move_piece_down(GameStruct_t *game){
    game->field[game->currentY++][game->currentX] = 0;
    game->field[game->currentY][game->currentX] = 1;
}


int canMoveRight(GameStruct_t *game){
     return 1;
    //проверить можно ли сдвинуть вправо
}
void moveRight(GameStruct_t *game){
    game->field[game->currentY][game->currentX++] = 0;
    game->field[game->currentY][game->currentX] = 1;
    //сдвинуть вправо
}


int canMoveLeft(GameStruct_t *game){
     return 1;
    //проверить можно ли сдвинуть влево
}
void moveLeft(GameStruct_t *game){
 
    //сдвинуть влево
}

void rotate_piece(GameStruct_t *game){
     return;
    //поворот фигуры
}