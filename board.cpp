#include"shape2D.hpp"
#include"piece.hpp"
#include"board.hpp"

#include <QDebug>

void Board::clearboard(){
    waiting = false;
    inGame = false;
    inPause = false;
    level = 1;
    npiece = 0;
    score = 0;
    nlines = 0;
    currentBoard.resize(WIDTH*HEIGHT);
    for(int i=0; i<WIDTH*HEIGHT; i++){
        currentBoard[i] = -1;
    }
}

void Board::drop(){
    int height = 0;
    int newY = currentY;
    while(newY < 20){
        if(!trymove(currentPiece, currentX, newY-1)){
            newY = newY - 2; // Imposible to go to newY-1 so stay at newY-2
            break;
        }
        newY++;
        height++;
    }
    currentY = newY;
    ndropped(height);
}

void Board::movedown(){
    if(!trymove(currentPiece, currentX, currentY+1)){
        ndropped(0);
    }
}

void Board::ndropped(int height){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            int x = currentX + i;
            int y = currentY + j;
            if(PIECE[currentPiece.getShape()][currentPiece.getOrientation()][i][j]==1){
                currentBoard[y*WIDTH + x] = currentPiece.getShape();
            }
        }
    }
    npiece ++;
    if(npiece % 20 == 0){
        level ++;
    }
    score += height + 7;

    removeline();
    newpiece();
}

void Board::removeline(){
    int nfullline = 0;
    for(int j = HEIGHT - 1; j>=0; j--){
        bool isfull = true;
        for(int i = 0; i<WIDTH; i++){
            if(currentBoard[j*WIDTH+i] == -1 || currentBoard[j*WIDTH+i] == 9){
                isfull = false;
                break;
            }
        }
        if(isfull){
            nfullline ++;
            for(int k = j-1; k >=0; k--){
                for(int i=0; i<WIDTH; i++){
                    currentBoard[(k+1)*WIDTH + i] = currentBoard[k*WIDTH + i];
                }
            }
            for(int i=0; i<WIDTH; i++){
                currentBoard[0*WIDTH + i] = -1;
            }
            j++;
        }
    }
    if(nfullline > 0){
        nlines += nfullline;
        switch(nfullline) {
        case 1 :
            score += level*40;
            break;
        case 2:
            score += level*100;
            break;
        case 3:
            score += level*300;
            break;
        case 4:
            score += level*400;
            break;
        default:
            break;
        }
    }
}

void Board::newpiece()
{
    currentX = 3;
    currentY = 0;
    currentPiece = nextPiece;
    nextPiece.setrandomShape();
    currentY = - currentPiece.getminY();
    if(!trymove(currentPiece, currentX, currentY)){
        inGame = false;
    }
    waiting = true;
}

bool Board::trymove(const Piece &newpiece, int nextX, int nextY){
    //std::cout << "boucle move 2" << std::endl;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(PIECE[currentPiece.getShape()][currentPiece.getOrientation()][i][j] == 1 && currentBoard[(nextY + j)*WIDTH + nextX + i] != -1){
                return false;
            }
        }
    }
    if (nextX + newpiece.getminX() < 0 || nextX + newpiece.getmaxX() >= WIDTH || nextY + newpiece.getmaxY() >= HEIGHT){
        return false;
    }
    currentPiece = newpiece;
    currentX = nextX;
    currentY = nextY;
    return true;
}

Piece Board::getPiece(){
    return currentPiece;
}

Piece Board::getNextPiece(){
    return nextPiece;
}

int Board::getX(){
    return currentX;
}

int Board::getY(){
    return currentY;
}

// Definition of MultiBoard

void MultiBoard::removeline(){
    twolines = false;
    int nfullline = 0;
    for(int j = HEIGHT - 1; j>=0; j--){
        bool isfull = true;
        for(int i = 0; i<WIDTH; i++){
            if(currentBoard[j*WIDTH+i] == -1 || currentBoard[j*WIDTH+i] == 9){
                isfull = false;
                break;
            }
        }
        if(isfull){
            nfullline ++;
            for(int k = j-1; k >=0; k--){
                for(int i=0; i<WIDTH; i++){
                    currentBoard[(k+1)*WIDTH + i] = currentBoard[k*WIDTH + i];
                }
            }
            for(int i=0; i<WIDTH; i++){
                currentBoard[0*WIDTH + i] = -1;
            }
            j++;
        }
    }
    if(nfullline > 0){
        nlines += nfullline;
        switch(nfullline) {
        case 1 :
            score += level*40;
            break;
        case 2:
            score += level*100;
            twolines = true;
            linedown();
            break;
        case 3:
            score += level*300;
            twolines = true;
            linedown();
            break;
        case 4:
            score += level*400;
            twolines = true;
            linedown();
            break;
        default:
            break;
        }
    }
}

void MultiBoard::plusopponentline()
{
    for(int j = 0; j<HEIGHT-1; j++){
        for(int i=0; i<WIDTH; i++){
            currentBoard[j*WIDTH + i] = currentBoard[(j+1)*WIDTH + i];
        }
    }
    for(int i=0; i<WIDTH; i++){
        currentBoard[(HEIGHT-1)*WIDTH + i] = 9;
    }
}

void MultiBoard::linedown()
{
    if(currentBoard[(HEIGHT-1)*WIDTH] == 9){ // Already lose one line
        for(int j=HEIGHT-1; j>=0; j--){
            for(int i=0; i<WIDTH; i++){
                currentBoard[(j+1)*WIDTH + i] = currentBoard[j*WIDTH + i];
            }
        }
        for(int i=0; i<WIDTH; i++){
            currentBoard[0*WIDTH + i] = -1;
        }
    }
}

void MultiBoard::clearboard(){
    waiting = false;
    inGame = false;
    inPause = false;
    level = 1;
    npiece = 0;
    score = 0;
    nlines = 0;
    twolines = false;
    victory = false;
    currentBoard.resize(WIDTH*HEIGHT);
    for(int i=0; i<WIDTH*HEIGHT; i++){
        currentBoard[i] = -1;
    }
}
