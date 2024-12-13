CC=gcc
CFLAGS=-Wall -Werror -Wextra -lpthread

# Default target
all: rebuild

my_treads_rw:
	$(CC) $(CFLAGS) treads_rw.c -o my_treads_rw
	
# Clean target
clean:
	rm -f my_treads_rw

# Rebuild target
rebuild: clean my_treads_rw

.PHONY: clean all my_treads_rw