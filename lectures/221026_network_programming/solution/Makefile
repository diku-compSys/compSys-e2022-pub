CC = gcc
CFLAGS =-Wall -Wextra -pedantic -std=gnu11
LD_FLAGS = -lpthread

all : echoclient echoserveri echoserverp echoservert

rebuild : clean all

csapp.o : csapp.c csapp.h
	$(CC) $(CFLAGS) -c $< -o $@

echoclient : echoclient.c csapp.o
	$(CC) $(CFLAGS) $< *.o -o $@ $(LD_FLAGS)

echoserveri : echoserveri.c processmessage.c csapp.o
	$(CC) $(CFLAGS) $< processmessage.c *.o -o $@ $(LD_FLAGS)

echoserverp : echoserverp.c processmessage.c csapp.o
	$(CC) $(CFLAGS) $< processmessage.c *.o -o $@ $(LD_FLAGS)

echoservert : echoservert.c processmessage.c csapp.o
	$(CC) $(CFLAGS) $< processmessage.c *.o -o $@ $(LD_FLAGS)

clean :
	rm -rf *.o echoclient echoserveri echoserverp echoservert
