# ===== Компилятор и флаги =====
CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Werror -pedantic
LDFLAGS  = -lncurses
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# ===== ОС и нужные флаги для Check =====
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CHECK_LIBS = -lcheck -lm -lsubunit
endif

ifeq ($(UNAME_S),Darwin)
    CHECK_LIBS = -lcheck -lm
endif 

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
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include/tetris

# ===== Тестовые файлы =====
TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))
TEST_BIN = test_app

# ===== Цель по умолчанию =====
all: clean $(LIB_NAME) $(EXE_NAME)

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
	install -d $(BINDIR) $(LIBDIR) $(INCLUDEDIR)
	install -m 755 $(EXE_NAME) $(BINDIR)/
	install -m 644 $(LIB_NAME) $(LIBDIR)/
	install -m 644 brick_game/tetris/*.h $(INCLUDEDIR)/

# ===== Удаление установленного =====
uninstall:
	rm -f $(BINDIR)/$(EXE_NAME)
	rm -f $(LIBDIR)/$(LIB_NAME)
	rm -rf $(INCLUDEDIR)
	-rmdir $(BINDIR) 2>/dev/null || true
	-rmdir $(LIBDIR) 2>/dev/null || true
	-rmdir $(PREFIX)/include 2>/dev/null || true
	-rmdir $(PREFIX) 2>/dev/null || true

# ===== Создание дистрибутива =====
PACKAGE_NAME = tetris
VERSION      = 1.0
DIST_DIR     = $(PACKAGE_NAME)-$(VERSION)
DIST_ARCHIVE = $(DIST_DIR).tar.gz

# ===== Создание дистрибутива =====
dist: clean
	@mkdir -p $(DIST_DIR)
	@cp -r brick_game $(DIST_DIR)/
	@cp -r docs $(DIST_DIR)/
	@cp -r gui $(DIST_DIR)/
	@cp -r tests $(DIST_DIR)/
	@cp Makefile $(DIST_DIR)/
	@tar -czf $(DIST_ARCHIVE) $(DIST_DIR)
	@rm -rf $(DIST_DIR)
	@echo "Distribution created: $(DIST_ARCHIVE)"

cppcheck:
	cppcheck --enable=all --inconclusive --std=c11 --quiet --force \
  --suppress=missingIncludeSystem $(SRC) $(SRC_UI) $(TEST_DIR)/

# ===== Цель: проверка на утечки памяти с помощью valgrind =====
valgrind: test_build
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes ./$(TEST_BIN)

# ===== Документация =====
DOC_DIR   = docs
DOC_SRC   = $(DOC_DIR)/tetris.texi
DOC_INFO  = $(DOC_DIR)/tetris.info
DOC_PDF   = $(DOC_DIR)/tetris.pdf
DOC_DVI   = $(DOC_DIR)/tetris.dvi

# Читать info docs/tetris.info
info: $(DOC_INFO)
$(DOC_INFO): $(DOC_SRC) | $(DOC_DIR)
	makeinfo $< -o $@

pdf: $(DOC_PDF)
$(DOC_PDF): $(DOC_SRC) | $(DOC_DIR)
	cd $(DOC_DIR) && texi2pdf ../$(DOC_SRC) -o $(notdir $@)

# Читать xdvi docs/tetris.dvi
dvi: $(DOC_DVI)
$(DOC_DVI): $(DOC_SRC) | $(DOC_DIR)
	cd $(DOC_DIR) && texi2dvi ../$(DOC_SRC)

# ===== Очистка документации =====
doc-clean:
	rm -f $(DOC_INFO) $(DOC_PDF) $(DOC_DVI)
	rm -f $(DOC_DIR)/tetris.*log $(DOC_DIR)/tetris.*toc $(DOC_DIR)/tetris.*aux
	rm -f $(DOC_DIR)/tetris.cp $(DOC_DIR)/tetris.fn $(DOC_DIR)/tetris.vr 
	rm -f $(DOC_DIR)/tetris.tp $(DOC_DIR)/tetris.pg $(DOC_DIR)/tetris.ky
	rm -f $(DOC_DIR)/tetris.fls $(DOC_DIR)/tetris.out $(DOC_DIR)/tetris.synctex.gz

# ===== Очистка =====
clean:
	rm -rf $(BUILD_DIR) $(EXE_NAME) $(LIB_NAME)
	rm -f *.info $(TEST_BIN) $(LIB_NAME)
	rm -rf coverage

format:
	clang-format -n -style=Google brick_game/tetris/*.c brick_game/tetris/*.h gui/cli/*.c gui/cli/*.h tests/*.c tests/*.h

.PHONY: all re test_build test coverage_build gcov_report clean install uninstall dist info pdf dvi doc-clean