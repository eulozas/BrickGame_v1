# ===== Компилятор и флаги =====
CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Werror -pedantic
LDFLAGS  = -lncurses

# ===== Директории =====
BUILD_DIR    = build
SRC_OBJ_DIR  = $(BUILD_DIR)/src
CLI_OBJ_DIR  = $(BUILD_DIR)/cli

# ===== Исходники и заголовки =====
SRC       = $(wildcard brick_game/tetris/*.c)
SRC_UI    = $(wildcard gui/cli/*.c)

OBJ       = $(patsubst brick_game/tetris/%.c,$(SRC_OBJ_DIR)/%.o,$(SRC))
OBJ_UI    = $(patsubst gui/cli/%.c,$(CLI_OBJ_DIR)/%.o,$(SRC_UI))

HEADERS   = $(wildcard brick_game/tetris/*.h) gui/cli/frontend.h

# ===== Имена артефактов =====
LIB_NAME  = libtetris.a
EXE_NAME  = tetris

# ===== Пути установки =====
PREFIX    ?= /usr/local

# ===== Цель по умолчанию =====
all: $(LIB_NAME) $(EXE_NAME)

# ===== Сборка библиотеки =====
$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

# ===== Сборка исполняемого файла =====
$(EXE_NAME): $(LIB_NAME) $(OBJ_UI)
	$(CC) -o $@ $(OBJ_UI) $(LIB_NAME) $(LDFLAGS)

# ===== Компиляция объектников =====
$(SRC_OBJ_DIR)/%.o: brick_game/tetris/%.c $(HEADERS) | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLI_OBJ_DIR)/%.o: gui/cli/%.c $(HEADERS) | $(CLI_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ===== Создание папок =====
$(SRC_OBJ_DIR):
	mkdir -p $@

$(CLI_OBJ_DIR):
	mkdir -p $@

# ===== Установка ===== make install PREFIX=/home/user/mytetris
install: $(EXE_NAME) $(LIB_NAME)
	mkdir -p $(PREFIX)/bin $(PREFIX)/lib $(PREFIX)/include/tetris
	cp $(EXE_NAME) $(PREFIX)/bin/
	cp $(LIB_NAME) $(PREFIX)/lib/
	cp brick_game/tetris/*.h $(PREFIX)/include/tetris/

# ===== Удаление установленного =====
uninstall:
	rm -f $(PREFIX)/bin/$(EXE_NAME)
	rm -f $(PREFIX)/lib/$(LIB_NAME)
	rm -rf $(PREFIX)/include/tetris
	-rmdir $(PREFIX)/bin 2>/dev/null || true
	-rmdir $(PREFIX)/lib 2>/dev/null || true
	-rmdir $(PREFIX)/include 2>/dev/null || true
	rm -rf $(PREFIX)

# ===== Очистка =====
clean:
	rm -rf $(BUILD_DIR) $(EXE_NAME) $(LIB_NAME)

.PHONY: all clean install uninstall

# all: tetris

# tetris: tetris.o backend.o frontend.o fsm.o helpers.o pieces.o
# 	$(CC) -o $@ $^ $(LDFLAGS)

# # компиляция tetris.o
# tetris.o: brick_game/tetris/tetris.c brick_game/tetris/backend.h brick_game/tetris/fsm.h brick_game/tetris/helpers.h brick_game/tetris/pieces.h
# 	$(CC) $(CFLAGS) -c brick_game/tetris/tetris.c -o tetris.o

# # компиляция backend.o
# backend.o: brick_game/tetris/backend.c brick_game/tetris/backend.h brick_game/tetris/fsm.h brick_game/tetris/helpers.h
# 	$(CC) $(CFLAGS) -c brick_game/tetris/backend.c -o backend.o 

# # компиляция frontend.o
# frontend.o: gui/cli/frontend.c brick_game/tetris/backend.h gui/cli/frontend.h brick_game/tetris/fsm.h
# 	$(CC) $(CFLAGS) -c gui/cli/frontend.c -o frontend.o

# # компиляция fsm.o
# fsm.o: brick_game/tetris/fsm.c brick_game/tetris/fsm.h
# 	$(CC) $(CFLAGS) -c brick_game/tetris/fsm.c -o fsm.o

# # компиляция pieces.o
# pieces.o: brick_game/tetris/pieces.c brick_game/tetris/pieces.h brick_game/tetris/backend.h brick_game/tetris/helpers.h
# 	$(CC) $(CFLAGS) -c brick_game/tetris/pieces.c -o pieces.o

# # компиляция helpers.o
# helpers.o: brick_game/tetris/helpers.c brick_game/tetris/helpers.h
# 	$(CC) $(CFLAGS) -c brick_game/tetris/helpers.c -o helpers.o

# # очистка
# clean:
# 	rm -f *.o tetris