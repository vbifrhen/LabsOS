CC=gcc
CFLAGS=-Wall -Werror -Wextra -lpthread

# Default target
all: rebuild

my_treads:
	$(CC) $(CFLAGS) treads.c -o my_treads
	
# Clean target
clean:
	rm -f my_treads

# Rebuild target
rebuild: clean my_treads

.PHONY: clean all my_treads