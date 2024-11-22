CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_pipe:
	$(CC) $(CFLAGS) pipe.c -o my_pipe 

my_fifo:
	$(CC) $(CFLAGS) fifo.c -o my_fifo 
	
# Clean target
clean:
	rm -f my_pipe my_fifo

# Rebuild target
rebuild: clean my_pipe my_fifo

.PHONY: clean all my_pipe my_fifo