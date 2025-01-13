#include"shape2D.hpp"
#include"piece.hpp"

#include <QDebug>
#include <QRandomGenerator>

void Piece::setShape(int aShape){
    shape = aShape;
}
void Piece::setrandomShape(){
    // need to pass from random (usual) to qrandom
    int newShape = QRandomGenerator::global()->bounded(0, 7);
    qDebug() << "random flower!" << newShape;
    shape = newShape;
}
const int Piece::getShape(){
    return shape;
}

Piece Piece::rotateL(){
    if(--orientation < 0)
        orientation = 3;
    return *this;
}
Piece Piece::rotateR(){
    if(++orientation > 3)
        orientation = 0;
    return *this;
}

const int Piece::getOrientation(){
    return orientation;
}

void Piece::setX(int aX){
    x = aX;
}
const int Piece::getX(){
    return x;
}

void Piece::setY(int aY){
    y = aY;
}
const int Piece::getY(){
    return y;
}

int Piece::getminX() const{
    int min = 4;
    for(int j=0; j<4; j++){
        for(int i=0; i<4; i++){
            if(PIECE[shape][orientation][i][j]==1 && i<min){
                min = i;
            }
        }
    }
    return min;
}

int Piece::getmaxX() const{
    int max = 0;
    for(int j=0; j<4; j++){
        for(int i=0; i<4; i++){
            if(PIECE[shape][orientation][i][j]==1 && i>max){
                max = i;
            }
        }
    }
    return max;
}

int Piece::getminY() const{
    int min = 4;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(PIECE[shape][orientation][i][j]==1 && j<min){
                min = j;
            }
        }
    }
    return min;
}

int Piece::getmaxY() const{
    int max = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(PIECE[shape][orientation][i][j]==1 && j>max){
                max = j;
            }
        }
    }
    return max;
}
