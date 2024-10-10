CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_fork:
	$(CC) $(CFLAGS) fork.c -o my_fork
	
# Clean target
clean:
	rm -f my_fork

# Rebuild target
rebuild: clean my_fork

.PHONY: clean all my_fork