#include "chessboard.h"
#include "chessbox.h"
#include "game.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"
#include <QDebug>
extern Game *game;
ChessBoard::ChessBoard()
{
    setUpBlack();
    setUpWhite();
}
void ChessBoard::drawBoxes(int x,int y)
{
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box = new ChessBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);
            game->addToScene(box);



        }
    }

}


void ChessBoard::addChessPiece() {
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {

            ChessBox *box =game->collection[i][j];
            if(i < 2) {
                static int k;
                box->placePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > 5) {
                static int h;
                box->placePiece(white[h]);
                game->alivePiece.append(white[h]);
                game->addToScene(white[h++]);

            }

        }
    }

}

void ChessBoard::setUpWhite()
{
    ChessPiece *piece;
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
         piece->num=i;
        white.append(piece);

    }
    piece = new Rook("WHITE");
    piece->num=8;
    white.append(piece);
    piece = new Knight("WHITE");
    piece->num=9;
    white.append(piece);
    piece = new Bishop("WHITE");
    piece->num=10;
    white.append(piece);

    piece = new Queen("WHITE");
    piece->num=11;
    white.append(piece);

    piece = new King("WHITE");
    piece->num=12;
    white.append(piece);

    piece = new Bishop("WHITE");
    piece->num=13;
    white.append(piece);

    piece = new Knight("WHITE");
    piece->num=14;
    white.append(piece);

    piece = new Rook("WHITE");
    piece->num=15;
    white.append(piece);

}

void ChessBoard::setUpBlack()
{
    ChessPiece *piece;
    piece = new Rook("BLACK");
    piece->num=16;
    black.append(piece);

    piece = new Knight("BLACK");
    piece->num=17;
    black.append(piece);

    piece = new Bishop("BLACK");
    piece->num=18;
    black.append(piece);

    piece = new Queen("BLACK");
    piece->num=19;
    black.append(piece);

    piece = new King("BLACK");
    piece->num=20;
    black.append(piece);
    piece = new Bishop("BLACK");
    piece->num=21;
    black.append(piece);
    piece = new Knight("BLACK");
    piece->num=22;
    black.append(piece);
    piece = new Rook("BLACK");
    piece->num=23;
    black.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        piece->num=24+i;
        black.append(piece);

    }
}


void ChessBoard::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            ChessBox *box =game->collection[i][j];
            box->setHasChessPiece(false);
            box->setChessPieceColor("NONE");
            box->currentPiece = NULL;
            if(i < 2) {

                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                game->alivePiece.append(black[k++]);

            }
            if(i > 5) {

                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                game->alivePiece.append(white[h++]);

            }

        }
    }
}
