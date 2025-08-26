#ifndef BACKEND_H
#define BACKEND_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH]; 
    int x, y; 
} GameState;

void init_game(GameState *game);

void move_left(GameState *game);
void move_right(GameState *game);
void move_down(GameState *game);

#endif