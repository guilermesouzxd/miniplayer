CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
BUILD = build
APP = $(BUILD)/miniplayer
.PHONY: all test clean
all: $(APP)
$(BUILD):
	mkdir -p $(BUILD)
$(APP): src/main.c src/miniplayer.c include/miniplayer.h | $(BUILD)
	$(CC) $(CFLAGS) src/main.c src/miniplayer.c -o $@
$(BUILD)/test_musica: tests/test_musica.c src/musica.c | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@
test: $(BUILD)/test_musica 
	@set -e; for t in $(BUILD)/test_musica; do echo "== $$t =="; ./$$t; done
clean:
	rm -rf $(BUILD)
