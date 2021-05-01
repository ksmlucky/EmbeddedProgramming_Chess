#include "chesspiece.h"
#include "game.h"
#include <QDebug>
#include "king.h"
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

#include "button.h"

extern Game *game;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int in=read(game->cfd,game->inmsg,14);

     if(in>0&&game->getTurn()=="WHITE")
       {
         game->changeTurn();
         //qDebug()<<game->inmsg<<"read Turn:"<<game->turn;
         replacePiece();
       }

    if(game->getTurn()=="BLACK")
    {
        //qDebug()<<"Choose";
    //Deselect
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced() )|| ( (game->getTurn() != this->getSide())&& (!game->pieceToMove)) )
        return;
    //selecting
    if(!game->pieceToMove){

        game->pieceToMove = this;
        game->pieceToMove->getCurrentBox()->setColor(Qt::red);
        game->pieceToMove->moves();
    }
    //Consuming counterPart of the CHessBox
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }

}

}
void ChessPiece::replacePiece()
{
    QString num(game->inmsg);
    QStringList list=num.split(" ");
    int n=list[0].toInt();
    int x=list[1].toInt();
    int y=list[2].toInt();
    int c=list[3].toInt();
    for(int i=0;i<16;i++)
    {
        if(n==game->chess->white[i]->num)
        {
            game->chess->white[i]->setPos(x,y);
            int box_x=(x-300)/100;
            int box_y=y/100;
             qDebug()<<x<<y<<box_x<<box_y;
            game->chess->white[i]->setCurrentBox(game->collection[box_y][box_x]);
            game->collection[box_y][box_x]->setHasChessPiece(true,game->chess->white[i]);
            game->collection[box_y][box_x]->currentPiece=game->chess->white[i];
        }
    }
    if(c!=50)
    {
        for(int i=0;i<16;i++)
            if(c==game->chess->black[i]->num)
            {
                game->placeInDeadPlace(game->chess->black[i]);
            }
    }
}
void ChessPiece::setCurrentBox(ChessBox *box)
{

    currentBox = box;
}

ChessBox *ChessPiece::getCurrentBox()
{
    return currentBox;
}

QString ChessPiece::getSide()
{
    return side;
}

void ChessPiece::setSide( QString value)
{
    side = value;
}

bool ChessPiece::getIsPlaced()
{
    return isPlaced;
}

void ChessPiece::setIsPlaced(bool value)
{
    isPlaced = value;

}
QList<ChessBox *> ChessPiece::moveLocation()
{
    return location;
}
void ChessPiece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

bool ChessPiece::boxSetting(ChessBox *box)
{
    if(box->getHasChessPiece()) {
        King *q = dynamic_cast<King*>(location.last()->currentPiece);
        if(q){
            box->setColor(Qt::blue);
        }
        else
            box->setColor(Qt::red);
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}
