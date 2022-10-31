CC = gcc
CFLAGS =-Wall -Wextra -pedantic -std=gnu11
LD_FLAGS = -lpthread

all : echoclient echoserver

rebuild : clean all

csapp.o : csapp.c csapp.h
	$(CC) $(CFLAGS) -c $< -o $@

echoclient : echoclient.c csapp.o
	$(CC) $(CFLAGS) $< *.o -o $@ $(LD_FLAGS)

echoserver : echoserver.c csapp.o
	$(CC) $(CFLAGS) $< *.o -o $@ $(LD_FLAGS)

clean :
	rm -rf *.o echoclient echoserver
