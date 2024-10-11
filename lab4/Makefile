CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_chmod:
	$(CC) $(CFLAGS) chmod.c -o my_chmod
	
# Clean target
clean:
	rm -f my_chmod

# Rebuild target
rebuild: clean my_chmod

.PHONY: clean all my_chmod