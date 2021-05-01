#ifndef NETWORK_H
#define NETWORK_H
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "button.h"

class network
{
public:
    network();
    void readLine(int fd, char* str);
    int Server(int p);
private:
    int sfd, cfd, port, clientlen;
    struct sockaddr_in serveraddr, clientaddr;
    struct hostent *hp;
    char *haddrp;
};

#endif // NETWORK_H
