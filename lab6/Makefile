CC=gcc
CFLAGS=-Wall -Werror -Wextra

# Default target
all: rebuild

my_cat:
	$(CC) $(CFLAGS) cat.c -o my_cat 

my_grep:
	$(CC) $(CFLAGS) grep.c -o my_grep 
	
# Clean target
clean:
	rm -f my_cat my_grep

# Rebuild target
rebuild: clean my_cat my_grep

.PHONY: clean all my_cat my_grep