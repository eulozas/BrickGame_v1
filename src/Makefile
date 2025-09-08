CC = gcc
CFLAGS = -std=c11
LDFLAGS = -lncurses

all: tetris

tetris: tetris.o backend.o frontend.o fsm.o helpers.o pieces.o
	$(CC) -o $@ $^ $(LDFLAGS)

# компиляция tetris.o
tetris.o: brick_game/tetris/tetris.c brick_game/tetris/backend.h brick_game/tetris/fsm.h brick_game/tetris/helpers.h brick_game/tetris/pieces.h
	$(CC) $(CFLAGS) -c brick_game/tetris/tetris.c -o tetris.o

# компиляция backend.o
backend.o: brick_game/tetris/backend.c brick_game/tetris/backend.h brick_game/tetris/fsm.h brick_game/tetris/helpers.h
	$(CC) $(CFLAGS) -c brick_game/tetris/backend.c -o backend.o 

# компиляция frontend.o
frontend.o: gui/cli/frontend.c brick_game/tetris/backend.h gui/cli/frontend.h brick_game/tetris/fsm.h
	$(CC) $(CFLAGS) -c gui/cli/frontend.c -o frontend.o

# компиляция fsm.o
fsm.o: brick_game/tetris/fsm.c brick_game/tetris/fsm.h
	$(CC) $(CFLAGS) -c brick_game/tetris/fsm.c -o fsm.o

# компиляция pieces.o
pieces.o: brick_game/tetris/pieces.c brick_game/tetris/pieces.h brick_game/tetris/backend.h brick_game/tetris/helpers.h
	$(CC) $(CFLAGS) -c brick_game/tetris/pieces.c -o pieces.o

# компиляция helpers.o
helpers.o: brick_game/tetris/helpers.c brick_game/tetris/helpers.h
	$(CC) $(CFLAGS) -c brick_game/tetris/helpers.c -o helpers.o

# очистка
clean:
	rm -f *.o tetris