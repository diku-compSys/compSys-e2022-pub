CC=gcc
CFLAGS=-Wall -Wextra -pedantic
PROGRAMS=exec0 exec1 fork0 fork1 fork2 forkbomb pipe0 zombies forks

all: $(PROGRAMS)

%: %.c
	$(CC) -o $@ $^ $(CFLAGS)
