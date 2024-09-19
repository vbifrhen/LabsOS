CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Build directory
BUILD_DIR=../build

# Default target
all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) ./s21_cat.c -o ./s21_cat 
	
# Clean target
clean:
	rm -f ./s21_cat

# Rebuild target
rebuild: clean all

.PHONY: clean all s21_cat