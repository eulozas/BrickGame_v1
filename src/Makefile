CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lncurses

all: tetris

tetris: tetris.o backend.o frontend.o
	$(CC) -o $@ $^ $(LDFLAGS)

# компиляция tetris.o
tetris.o: tetris.c brick_game/tetris/backend.h
	$(CC) $(CFLAGS) -c tetris.c -o tetris.o

# компиляция backend.o
backend.o: brick_game/tetris/backend.c brick_game/tetris/backend.h
	$(CC) $(CFLAGS) -c brick_game/tetris/backend.c -o backend.o

# компиляция frontend.o
frontend.o: gui/cli/frontend.c brick_game/tetris/backend.h gui/cli/frontend.h
	$(CC) $(CFLAGS) -c gui/cli/frontend.c -o frontend.o

# очистка
clean:
	rm -f *.o tetris