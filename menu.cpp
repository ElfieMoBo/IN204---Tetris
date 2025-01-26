#include "menu.hpp"
#include "server.hpp"

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

#include <iostream>

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    tokill = true;
    //std::cout <<  "menu created" << std::endl;
    setPalette(QPalette(QColor(244, 239, 228)));
    setAutoFillBackground(true);
    QFont writing("Cursive", 10, QFont::Medium, true);

    solobutton = new QPushButton(tr("Solo"));
    solobutton->setStyleSheet((QString)"QPushButton {background-color: #bbb5e9; color: #fdfaf3}");
    solobutton->setFont(writing);
    solobutton->setFocusPolicy(Qt::NoFocus);
    multibutton= new QPushButton(tr("Multi"));
    multibutton->setStyleSheet((QString)"QPushButton {background-color: #bbb5e9; color: #fdfaf3}");
    multibutton->setFont(writing);
    multibutton->setFocusPolicy(Qt::NoFocus);
    quit = new QPushButton(tr("Quit"));
    quit->setStyleSheet((QString)"QPushButton {background-color: #bbb5e9; color: #fdfaf3}");
    quit->setFont(writing);

    QLabel *label = new QLabel(tr("photo.png"));
    label->setPixmap(QPixmap("C:\\Users\\elfie\\OneDrive\\Documents\\travail\\ensta_2a\\informatique\\in204\\projet\\tetrisv2\\tetris_menu (1).png"));
    label->setAlignment(Qt::AlignCenter);

    QHBoxLayout* down_layout = new QHBoxLayout;
    down_layout->addWidget(solobutton);
    down_layout->addWidget(multibutton);

    QGridLayout *grid = new QGridLayout;
    grid->addLayout(down_layout,2,0);
    grid->addWidget(quit,3,0);
    grid->addWidget(label,0,0);
    setLayout(grid);
    label->show();

    setWindowTitle(tr("Tetris : player 1"));
    resize(200, 200);

    connect(solobutton, &QPushButton::clicked, this, &Menu::solo);
    connect(multibutton,  &QPushButton::clicked, this, &Menu::multi);
    connect(quit , &QPushButton::clicked, qApp, &QCoreApplication::quit);
}

void Menu::solo()
{
    Show *game = new Show;
    game->show();
    if(tokill){
        this->deleteLater();
    } else {
        this->hide();
    }
}

void Menu::multi()
{
    Server *game = new Server;
    game->show();
    if(tokill){
        this->deleteLater();
    } else {
        this->hide();
    }
}

Menu::~Menu()
{
    delete solobutton;
    delete multibutton;
    delete quit;
    std::cout << "menu destructed" << std::endl;
}
