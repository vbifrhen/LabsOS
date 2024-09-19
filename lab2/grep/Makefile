CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Build directory
BUILD_DIR=../build

# Default target
all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) ./s21_grep.c -o ./s21_grep 

# Clean target
clean:
	rm -f ./s21_grep

# Rebuild target
rebuild: clean all

.PHONY: clean all s21_grep
