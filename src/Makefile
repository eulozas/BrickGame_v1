CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
LDFLAGS=-lncurses

all: tetris

tetris: tetris.o backend.o frontend.o
	$(CC) -o tetris tetris.o backend.o frontend.o $(LDFLAGS)

tetris.o: brick_game/tetris/tetris.c brick_game/tetris/backend.h
	$(CC) $(CFLAGS) -c brick_game/tetris/tetris.c

backend.o: brick_game/tetris/backend.c brick_game/tetris/backend.h
	$(CC) $(CFLAGS) -c brick_game/tetris/backend.c

frontend.o: gui/cli/frontend.c brick_game/tetris/backend.h
	$(CC) $(CFLAGS) -c gui/cli/frontend.c

clean:
	rm -f *.o tetris