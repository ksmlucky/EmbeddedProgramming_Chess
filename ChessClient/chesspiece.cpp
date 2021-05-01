#include "chesspiece.h"
#include "game.h"
#include <QDebug>
#include "king.h"

extern Game *game;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(start==true){
    //int in=game->readLine(game->cfd,game->inmsg);
      int in=read(game->cfd,game->inmsg,14);
        if(in>0&&game->getTurn()=="BLACK")
      {
          game->changeTurn();
          //qDebug()<<game->inmsg<<"read Turn:"<<game->turn;
          replacePiece();
      }

    }
    start=true;
    if(game->getTurn()=="WHITE"){
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
        if(n==game->chess->black[i]->num)
        {
            game->chess->black[i]->setPos(x,y);
            int box_x=(x-300)/100;
            int box_y=y/100;
            qDebug()<<box_x<<box_y;
            game->chess->black[i]->setCurrentBox(game->collection[box_y][box_x]);
            game->collection[box_y][box_x]->setHasChessPiece(true,game->chess->black[i]);
            game->collection[box_y][box_x]->currentPiece=game->chess->black[i];
        }
    }
    if(c!=50)
    {
        for(int i=0;i<16;i++)
            if(c==game->chess->white[i]->num)
            {
                game->placeInDeadPlace(game->chess->white[i]);
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
QList<ChessBox *> ChessPiece::moveLocation()//possible location to move
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
