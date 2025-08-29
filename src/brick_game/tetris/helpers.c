
#include "helpers.h"

void spawn_new_piece(GameState *game){
     game->field[game->currentY][game->currentX] = 1;
    //нужно сгенерить новую фигуру для некст, а некст перенести в текущую
}


void move_piece_down(GameState *game){
    game->field[game->currentY++][game->currentX] = 0;
    game->field[game->currentY][game->currentX] = 1;
}


int canMoveLeft(GameState *game){
     return 1;
    //проверить можно ли сдвинуть влево
}
void moveLeft(GameState *game){
    return;
    //сдвинуть влево
}

void rotate_piece(GameState *game){
     return;
    //поворот фигуры
}