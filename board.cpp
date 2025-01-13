#include"shape2D.hpp"
#include"piece.hpp"
#include"board.hpp"

#include<iostream>

#include <QDebug>

void Board::view(const Piece &cpiece){
    int old[4][4] = {{0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
    for(int i=currentX; i<currentX+4; i++){
        for(int j=currentY; j < currentY+4; j++){
            old[i-currentX][j-currentY] = currentBoard[j*WIDTH+i];
            if(PIECE[currentPiece.getShape()][currentPiece.getOrientation()][i-currentX][j-currentY]==1){
                currentBoard[j*WIDTH+i] = currentPiece.getShape();
            }
        }
    }
    auto start = currentBoard.begin();
    auto last = currentBoard.end();
    int ligne = 0;
    if(start!=last){
        if(*start==-1)
            std::cout << " ";
        else
            std::cout << *start;
        start ++;
        ligne ++;
        while(start != last){
            if(ligne==10){
                ligne = 0;
                std::cout<< std::endl;
            } else {
                std::cout << "|";
            }
            ligne ++;
            if(*start==-1)
                std::cout << " ";
            else
                std::cout << *start;
            start ++;
        }
    }
    std::cout << std::endl;

    std::cout << std::endl;
    for(int i=currentX; i<currentX+4; i++){
        for(int j=currentY; j < currentY+4; j++){
            if(PIECE[currentPiece.getShape()][currentPiece.getOrientation()][i-currentX][j-currentY]==1)
                currentBoard[j*WIDTH+i] = old[i-currentX][j-currentY];
        }
    }
}

void Board::clearboard(){
    //std::vector<int> currentBoard;
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
    if(!trymove(currentPiece, currentX, currentY-1))
        ndropped(0);
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
    std::cout << "Score: " << score << std::endl;
    std::cout << "Level: " << level << std::endl;
}

void Board::removeline(){
    int nfullline = 0;
    for(int j = HEIGHT - 1; j>=0; j--){
        bool isfull = true;
        for(int i = 0; i<WIDTH; i++){
            if(currentBoard[j*WIDTH+i] == -1){
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
        score += 10*nfullline;
    }
}

void Board::newpiece()
{
    currentX = 3;
    currentY = 0;
    currentPiece = nextPiece;
    nextPiece.setrandomShape();
    currentY = - currentPiece.getminY();
    shownext();
    if(!trymove(currentPiece, currentX, currentY)){
        std::cout << "End of the game" << std::endl;
        inGame = false;
    }
    waiting = true;
}

void Board::shownext(){
    std::cout << "no." << std::endl;
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
