#pragma once

#include <QDebug>

class Piece{
private:
    int shape;
    int orientation;
    int x;
    int y;
public:
    Piece(): shape(3), orientation(0), x(3), y(0)
    {
        //qDebug() << "piece created";
    }
    Piece(int aShape, int anorientation): shape(aShape), orientation(anorientation), x(0), y(0)
    {
        //qDebug() << "piece created";
    }
    Piece(const Piece &anotherPiece):
        shape(anotherPiece.shape),
        orientation(anotherPiece.orientation),
        x(anotherPiece.x),
        y(anotherPiece.y)
    {
        //qDebug() << "piece created";
    }
    ~Piece()
    {
        //qDebug() << "piece destructed";
    }

    Piece operator=(const Piece& oldPiece);

    void setrandomShape();
    int getShape();

    Piece rotateL();
    Piece rotateR();
    int getOrientation();

    /* To get the real dimension of the piece */
    int getminX() const;
    int getmaxX() const;
    int getminY() const;
    int getmaxY() const;
};
