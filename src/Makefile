# ===== Компилятор и флаги =====
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
LDFLAGS = -lncurses

# # ===== Директории объектных файлов =====
# BUILD_DIR = build
# SRC_OBJ_DIR = $(BUILD_DIR)/src
# CLI_OBJ_DIR = $(BUILD_DIR)/cli

# # ===== Файлы библиотеки =====
# SRC = $(wildcard brick_game/tetris/*.c)
# OBJ = $(patsubst brick_game/tetris/%.c, $(SRC_OBJ_DIR)/%.o, $(SRC))
# # Все заголовки игровой логики
# HEADERS = $(wildcard brick_game/tetris/*.h)

# SRC_UI := $(wildcard gui/cli*.c)
# OBJ_UI = $(patsubst gui/cli/%.c,$(CLI_OBJ_DIR)/%.o,$(SRC_UI))

# LIB_NAME = libtetris.a
# EXE_NAME = tetris

# # ===== Цель: all (полная сборка, запуск и отчёт покрытия) =====
# all: $(EXE_NAME)

# # ===== Исполняемый файл =====
# $(EXE_NAME): libtetris.a $(OBJ_UI)
# 	$(CC) -o $@ $(OBJ_UI) $(LIB_NAME) $(LDFLAGS)

# # ===== Цель: сборка библиотеки без покрытия =====
# libtetris.a: $(OBJ)
# 	ar rcs $(LIB_NAME) $(OBJ)
# 	ranlib $(LIB_NAME)



# # ===== Создание папок =====
# $(SRC_OBJ_DIR):
# 	mkdir -p $(SRC_OBJ_DIR)

# $(CLI_OBJ_DIR):
# 	mkdir -p $(CLI_OBJ_DIR)

# # ===== Компиляция объектных файлов библиотеки =====
# $(SRC_OBJ_DIR)/%.o: brick_game/tetris/%.c $(HEADERS) | $(SRC_OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # ===== Компиляция объектных файлов интерфейса =====
# $(CLI_OBJ_DIR)/%.o: gui/cli/%.c gui/cli/frontend.h | $(CLI_OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # ===== Очистка =====
# clean:
# 	rm -rf $(BUILD_DIR) $(EXE_NAME)


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