CC = gcc

NotAVim: main.c
	$(CC) main.c -o NotAVim -Wall -Wextra -pedantic -std=c99