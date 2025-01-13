#pragma once

#include"piece.hpp"

#include<vector>

const int HEIGHT = 20;
const int WIDTH = 10;

class Board
{
private:
    Piece currentPiece;
    int currentX;
    int currentY;
    Piece nextPiece;
    std::vector<int> currentBoard;
    bool waiting;
    bool inGame;
    bool inPause;
    int level;
    int npiece;
    unsigned int score;
    int nlines;
public:

    Board(): currentPiece(), currentX(3), currentY(0), nextPiece(), currentBoard(), waiting(false), level(1), npiece(0), score(0), nlines(0), inGame(true), inPause(false)
    {
        std::vector<int> currentBoard;
        currentBoard.resize(WIDTH*HEIGHT);
        for(int i=0; i<WIDTH*HEIGHT; i++){
            currentBoard[i] = -1;
        }
    }

    void view(const Piece &piece);
    void clearboard();
    void drop();
    void movedown();
    void ndropped(int height);
    void removeline();
    void newpiece();
    void shownext();
    bool trymove(const Piece &newpiece, int newX, int newY);
    Piece getPiece();
    Piece getNextPiece();
    int getX();
    int getY();

    // displaying:
    unsigned int getScore(){
        return score;
    }
    void setScore(unsigned int newscore){
        score = newscore;
    }
    int getLevel(){
        return level;
    }
    void setLevel(int newlevel){
        level = newlevel;
    }
    int getLines(){
        return nlines;
    }
    void setLines(int newlines){
        nlines = newlines;
    }
    bool getGame(){
        return inGame;
    }
    void Game(){
        inGame = true;
    }
    bool getPause(){
        return inPause;
    }
    void reversePause(){
        inPause = !inPause;
    }
    bool getWaiting(){
        return waiting;
    }
    void reverseWaiting(){
        waiting = !waiting;
    }
    std::vector<int> getBoard(){
        return currentBoard;
    }
};
