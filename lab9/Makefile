CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_transmitting:
	$(CC) $(CFLAGS) transmitting.c -o my_transmitting 

my_accept:
	$(CC) $(CFLAGS) accept.c -o my_accept 
	
# Clean target
clean:
	rm -f my_transmitting my_accept

# Rebuild target
rebuild: clean my_transmitting my_accept

.PHONY: clean all my_transmitting my_accept