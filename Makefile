CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iinclude
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

SRC = main.c $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC)))
BIN = NotAVim

all: $(BUILD_DIR) $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN)