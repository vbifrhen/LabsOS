CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_archiver:
	$(CC) $(CFLAGS) archivator.c -o archiver
	
# Clean target
clean:
	rm -f archiver

# Rebuild target
rebuild: clean my_archiver

.PHONY: clean all my_archiver