/*
 * echoserveri.c - An iterative echo server
 */
/* $begin echoserverimain */
#include "csapp.h"

char var[64];

void *echo(void *vargp)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    int connfd = *((int *)vargp);
    Pthread_detach(pthread_self()); 
    Free(vargp);

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
		printf("server received %d bytes\n", (int)n);

        if (strcmp(buf, "ping\n") == 0)
        {
            memcpy(buf, "pong\n", 5);
            n = 5;
        }
        else if (strcmp(buf, "GET\n") == 0)
        {
            while (var[0] == '\0')
            {
                sleep(3);
            }
            memcpy(buf, var, strlen(var));
            n = strlen(var);
        }
        else if (strncmp(buf, "PUT ", 4) == 0)
        {
            memcpy(var, &buf[4], strlen(buf)-4);
            var[strlen(buf)-4] = '\0';
            memcpy(buf, "OK\n", 3);
            n = 3;
            printf("Set shared value to: '%s'\n", var);
        }
        else
        {
            memcpy(buf, "BAD REQUEST\n", 12);
            n = 12;
        }
        printf("Sending %ld bytes in response\n", n);
		Rio_writen(connfd, buf, n);
    }
    Close(connfd);
    return NULL;
}

int main(int argc, char **argv)
{
    int listenfd, *connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    memcpy(var, "\0", 1);

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);

        connfd = Malloc(sizeof(int)); 
	    *connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen); 
	    Pthread_create(&tid, NULL, echo, connfd);
    }
    exit(0);
}
/* $end echoserverimain */
