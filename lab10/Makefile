CC=gcc
CFLAGS=-Wall -Werror -Wextra -lpthread

# Default target
all: rebuild

my_treads_cond:
	$(CC) $(CFLAGS) treads_cond.c -o my_treads_cond
	
# Clean target
clean:
	rm -f my_treads_cond

# Rebuild target
rebuild: clean my_treads_cond

.PHONY: clean all my_treads_cond