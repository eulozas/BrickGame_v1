#include "helpers.h"

int loadHighScore(int *high_score) {
    FILE *file = fopen("brick_game/tetris/highscore.txt", "r");
    if (!file) {
        return 0;  // файла нет или ошибка открытия
    }

    if (fscanf(file, "%d", high_score) != 1) {
        fclose(file);
        return 0;  // не удалось считать число
    }

    fclose(file);
    return 1;
}







// int canMoveRight(GameStruct_t *game){
//      return 1;
//     //проверить можно ли сдвинуть вправо
// }
// void moveRight(GameStruct_t *game){
//     game->field[game->currentY][game->currentX++] = 0;
//     game->field[game->currentY][game->currentX] = 1;
//     //сдвинуть вправо
// }


// int canMoveLeft(GameStruct_t *game){
//      return 1;
//     //проверить можно ли сдвинуть влево
// }
// void moveLeft(GameStruct_t *game){
 
//     //сдвинуть влево
// }

// void rotate_piece(GameStruct_t *game){
//      return;
//     //поворот фигуры
// }