#pragma once

class Piece{
private:
    int shape;
    int orientation;
    int x;
    int y;
public:
    Piece(): shape(3), orientation(0), x(3), y(0)
    {}
    Piece(int aShape, int anorientation): shape(aShape), orientation(anorientation), x(0), y(0)
    {}
    Piece(const Piece &anotherPiece):
        shape(anotherPiece.shape),
        orientation(anotherPiece.orientation),
        x(anotherPiece.x),
        y(anotherPiece.y)
    {}

    void setShape(int aShape);
    void setrandomShape();
    const int getShape();

    Piece rotateL();
    Piece rotateR();
    const int getOrientation();

    void setX(int aX);
    const int getX();

    void setY(int aY);
    const int getY();

    /* To get the real dimension of the piece */
    int getminX() const;
    int getmaxX() const;
    int getminY() const;
    int getmaxY() const;
};
