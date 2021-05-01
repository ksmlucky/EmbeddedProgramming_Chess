#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chessboard.h>
#include "chesspiece.h"
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
#include "button.h"
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructors
    Game(QWidget *parent = 0);

    //public Methods
    void drawDeadHolder(int x, int y, QColor color);
    void drawChessBoard();
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    //getters/setters
    ChessPiece *pieceToMove;

    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();
    int readLine(int fd,char* str);

    int fd;
    QString buffer;
    char inmsg[100],outmsg[100];

    int sfd, cfd, port, clientlen;
    struct sockaddr_in serveraddr, clientaddr;
    struct hostent *hp;
    char *haddrp;

    ChessBox *collection[8][8]; //Have to send where chess is really working
    QGraphicsTextItem *check;
    QList <ChessPiece *> alivePiece;
    void displayMainMenu();

    void gameOver();
    void removeAll();

    QGraphicsScene *gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn; //Have to send
    ChessBoard *chess;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turnDisplay;
public slots:
    void start();
    void Server();

};

#endif // GAME_H
