CC=gcc
CFLAGS=-Wall -Wextra -pedantic

all: exec0 exec1 fork0 fork1 fork2 forkbomb pipe0

%: %.c
	$(CC) -o $@ $^ $(CFLAGS)
