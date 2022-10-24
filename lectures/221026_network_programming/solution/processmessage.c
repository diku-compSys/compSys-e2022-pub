/*
 * processmessage - read and process text lines until client closes connection
 */
/* $begin processmessage */
#include "csapp.h"
#include <string.h>

void processmessage(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    char res[MAXLINE];
    char *s;
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) 
    {
        printf("Server recieved a message of %d bytes and length %d. \n", (int)n, strlen(buf));

        s = strstr(buf, "ping");
        if (s != NULL)
        {
            buf[1] = 'o';
            Rio_writen(connfd, buf, n);
        }
        else
        {
            strncpy(res, "BAD REQUEST\n", MAXLINE);
            Rio_writen(connfd, res, strlen(res));
        }
    }
}
/* $end processmessage */
