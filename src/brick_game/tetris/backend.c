#include "backend.h"
#include <string.h>

void init_game(GameState *game) {
    memset(game->field, 0, sizeof(game->field));
    game->x = FIELD_WIDTH / 2;
    game->y = 0;
}

void move_left(GameState *game) {
    if (game->x > 0) game->x--;
}

void move_right(GameState *game) {
    if (game->x < FIELD_WIDTH - 1) game->x++;
}

void move_down(GameState *game) {
    if (game->y < FIELD_HEIGHT - 1) game->y++;
}
