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

class network
{
public:
    network();
    int Client();
    int getFd();
    void readLine(int fd, char* str);

    int fd, port, result;
    char *host;
    struct sockaddr_in serveraddr;
    struct hostent *hp;

private:

};

#endif // NETWORK_H
