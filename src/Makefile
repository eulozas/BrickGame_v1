# ===== Компилятор и флаги =====
CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Werror -pedantic
LDFLAGS  = -lncurses
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lm -lsubunit

# ===== Директории =====
BUILD_DIR    = build
SRC_OBJ_DIR  = $(BUILD_DIR)/src
CLI_OBJ_DIR  = $(BUILD_DIR)/cli
TEST_OBJ_DIR = $(BUILD_DIR)/tests

# ===== Файлы и папки отчетности =====
COV_DIR = coverage
COV_INFO = coverage.info
COV_FILTERED = coverage_filtered.info

# ===== Включение флагов покрытия при необходимости =====
GCOV ?= 0
ifeq ($(GCOV), 1)
    CFLAGS += $(GCOV_FLAGS)
endif

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

# ===== Тестовые файлы =====
TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))
TEST_BIN = test_app

# ===== Цель по умолчанию =====
all: $(LIB_NAME) $(EXE_NAME)

# ===== Цель: полная пересборка без покрытия =====
re: clean $(LIB_NAME) test_build

# ===== Сборка библиотеки =====
$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

# ===== Сборка исполняемого файла =====
$(EXE_NAME): $(LIB_NAME) $(OBJ_UI)
	$(CC) -o $@ $(OBJ_UI) $(LIB_NAME) $(LDFLAGS)

# ===== Цель: сборка тестового приложения без покрытия =====
test_build: $(TEST_BIN)

# ===== Цель: запуск тестов (предполагается, что собраны) =====
test: test_build
	./$(TEST_BIN)

# ===== Цель: сборка с покрытием (пересборка библиотеки и тестов с флагами покрытия) =====
coverage_build:
	$(MAKE) clean
	$(MAKE) GCOV=1 $(LIB_NAME)
	$(MAKE) GCOV=1 test_build

# ===== Цель: генерация отчёта покрытия, зависит от сборки с покрытием и запуска тестов =====
gcov_report: re coverage_build
	./$(TEST_BIN)
	lcov --capture --directory . --output-file $(COV_INFO) --rc branch_coverage=1
	lcov --remove $(COV_INFO) '*/$(TEST_DIR)/*' --output-file $(COV_FILTERED) --rc branch_coverage=1
	genhtml $(COV_FILTERED) --output-directory $(COV_DIR) --rc branch_coverage=0

# ===== Сборка тестового приложения =====
$(TEST_BIN): $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -I. $(TEST_OBJ) $(LIB_NAME) -o $(TEST_BIN) $(CHECK_LIBS)

# ===== Компиляция объектников =====
$(SRC_OBJ_DIR)/%.o: brick_game/tetris/%.c $(HEADERS) | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLI_OBJ_DIR)/%.o: gui/cli/%.c $(HEADERS) | $(CLI_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(HEADERS) $(TEST_DIR)/test_header.h | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -I. -I$(TEST_DIR) -c $< -o $@

# ===== Создание папок =====
$(SRC_OBJ_DIR):
	mkdir -p $@

$(CLI_OBJ_DIR):
	mkdir -p $@

$(TEST_OBJ_DIR):
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
	rm -f *.info $(TEST_BIN) $(LIB_NAME)
	rm -rf coverage

.PHONY: all clean install uninstall