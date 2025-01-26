#include <unistd.h>

#include "menu.hpp"
#include "board.hpp"

#include <QApplication>
#include <QPushButton>
#include <QLabel>

extern Board gameboard;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("tetrisv2.ico"));
    Menu w;
    w.setKill(false);
    w.show();
    return a.exec();
}
