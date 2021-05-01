#include "network.h"
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
#include <QDebug>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 0

extern Game *game;
network::network()
{

}



int network::Server(int p)
{

    signal(SIGCHLD, SIG_IGN);

    port=4200;

    sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

    bzero((char*) &serveraddr, sizeof (serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(4200);
    printf("%hu, %u, %hu\n",serveraddr.sin_family,serveraddr.sin_addr.s_addr,serveraddr.sin_port);

    int a=bind(sfd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(sfd, 5);
    clientlen = sizeof(clientaddr);
    socklen_t client;
    client=clientlen;
    cfd = accept(sfd, (struct sockaddr*)&clientaddr, &client);
    hp=gethostbyaddr((char*)&clientaddr.sin_addr.s_addr,sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    haddrp = inet_ntoa(clientaddr.sin_addr);
    qDebug()<<"Server"<< haddrp <<"is connected to" <<clientaddr.sin_port;
    if(fork()==0)
    {
        while(1)
        {
            game->readLine(cfd,game->inmsg);
        }
    }
    return sfd;
}
