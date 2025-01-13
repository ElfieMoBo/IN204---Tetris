#include<iostream>
#include<thread>
//#include<chrono>
#include <unistd.h>
//#include <termios.h>

#include "show.hpp"
#include "qboard.hpp"
#include "board.hpp"

#include <QApplication>
#include <QPushButton>
#include <QLabel>


extern Board gameboard;

/*void automove(){
    gameboard.clearboard();
    while(gameboard.getGame()){
        if(!gameboard.getWaiting() && !gameboard.getPause()){
            if(!gameboard.trymove(gameboard.getPiece(), gameboard.getX(), gameboard.getY() + 1)){
                gameboard.ndropped(0);
            }
            gameboard.view(gameboard.getPiece());
            //qint time = 5;
            int time = (1000/(1 + gameboard.getLevel()))*1000;
            usleep(time);
        }
    }
}*/

/*void noCanon(){
    // ICANON (option): no need to press 'enter'
    struct termios icanon;
    tcgetattr(STDIN_FILENO, &icanon);
    icanon.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &icanon);
}*/

/*char keypress(){
    char buffer = 0;
    read(STDIN_FILENO, &buffer, 1);
    return buffer;
}*/

/*void charmove(){
    char lettre;
    while(gameboard.getGame()){
        lettre = keypress();
        if (lettre == 27 && !gameboard.getPause()) {
            char next = keypress();
            if (next == 91) { // Arrow (?)
                char direction = keypress();
                switch (direction) {
                case 'A': // up
                    gameboard.trymove(gameboard.getPiece().rotateR(), gameboard.getX(), gameboard.getY());
                    break;
                case 'B': // down
                    gameboard.trymove(gameboard.getPiece().rotateL(), gameboard.getX(), gameboard.getY());
                    break;
                case 'C': // right
                    gameboard.trymove(gameboard.getPiece(), gameboard.getX()+1, gameboard.getY());
                    break;
                case 'D': // left
                    gameboard.trymove(gameboard.getPiece(), gameboard.getX()-1, gameboard.getY());
                    break;
                default:
                    std::cout << "Autre touche spéciale" << std::endl;
                    break;
                }
            }
            gameboard.view(gameboard.getPiece());
        } else if (lettre == ' ') {
            gameboard.drop();
            gameboard.view(gameboard.getPiece());
        } else if (lettre == 'p') {
            gameboard.reversePause();
        } else if (lettre == 'q') {
            gameboard.reverseGame();
        }
    }
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Show w;
    w.show();
    gameboard.clearboard();
    return a.exec();
}
