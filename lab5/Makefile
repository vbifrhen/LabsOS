CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_chmod:
	$(CC) $(CFLAGS) archivator.c -o archiver
	
# Clean target
clean:
	rm -f archiver

# Rebuild target
rebuild: clean archiver

.PHONY: clean all archiver