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
#include<stdlib.h>
#include <string.h>
#include "game.h"
#include <QDebug>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 0

extern Game *game;
network::network()
{

}

void network::readLine(int fd, char* str)
{
    int n;
    do{
        n = read(fd, str,1);
    }while(n>0 && *str++ != '\0');
}

int network::getFd()
{
    return fd;
}

int network::Client()
{

    host="192.168.1.12";
    port=4200;

    fd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
    hp=gethostbyname(host);
    printf("%s\n",host);
    bzero((char*) &serveraddr, sizeof (serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char*)hp->h_addr_list[0],(char*)&serveraddr.sin_addr.s_addr,hp->h_length);
    serveraddr.sin_port = htons(port);
    do{
        result=connect(fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(result==-1)
    {
        sleep(1);
        printf("Connecting...\n");
    }}while(result==-1);
    qDebug()<<"Coneected to Server Use:"<<fd;
    if(fork()==0)
    {
        while(1)
        {
            int a=recv(fd,&(game->buffer),sizeof(game->buffer)+1,0);
            if(a!=-1)
                qDebug()<<game->buffer;
        }
    }
    return fd;
}
