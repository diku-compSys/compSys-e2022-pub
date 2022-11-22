#include "csapp.h"

struct payload_package {
    char* host;
    char* port;
};

// Very simple server, that will serve a client given as vargp.
// It will simply send the `message` to the client and then close the
// connection.
void* server(void* vargp){
    int connfd = *((int*) vargp);
    Pthread_detach(Pthread_self());
    Free(vargp);
    rio_t rio;
    char buf[MAXLINE];
    rio_readinitb(&rio,connfd);
    char* message = "this a very important message, do not share \n";
    int length = strlen(message) + 1 ;
    memcpy(buf,&length, 4 );
    memcpy(buf+4, message, length);
    Rio_writen(connfd,buf, 4 +length);
    Close(connfd);
    return 0;
}

// Client will receive message from server gien in `vargp` an print this
// to the terminal.
void* client(void* vargp) {
    struct payload_package p = *(struct payload_package *) vargp;
    rio_t rio;
    char buf[MAXLINE];

    while (1){
        int clientfd = Open_clientfd(p.host, p.port);
        if (clientfd) {
            Rio_readinitb(&rio, clientfd);
            Rio_readnb(&rio, buf, 4);
            int length = *(int*)buf;
            Rio_readnb(&rio, buf, length);
            printf("message is %s \n", buf);
        } else {
            printf("connection went wrong trying again in 5 seconds \n");
        }
            Sleep(5);
    }
    exit(0);
}

int main (int argc, char** argv) {
    int listenfd, *connfdp;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    char* c_host = argv[2]; // ip of peer
    char* c_port = argv[3]; // port of peer

    if (argc != 5) {
        exit(1);
    }

    pthread_t cid;
    struct payload_package p;
    p.host = c_host;
    p.port = c_port;

    // If -p is given as the last argument, we should not act as client,
    // since there is no server.
    if (strncmp("-p", argv[4], 2) != 0) {
        Pthread_create(&cid, NULL, client, &p);
    }

    listenfd = Open_listenfd(argv[1]);

    // Listen for connections and spawn threads to service them
    while (1) {
        clientlen=sizeof(struct sockaddr_storage);
        connfdp = Malloc(sizeof(int));
        *connfdp = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        Pthread_create(&tid, NULL, server, connfdp);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s) via thread %lu\n",
           client_hostname, client_port, (long) tid);
    }
    return 0;
}
