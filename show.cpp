#include "show.hpp"
#include "qboard.hpp"
#include "menu.hpp"
#include "server.hpp"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QLineEdit>

#include <iostream>

// Construction of the game apparence
Show::Show(QWidget *parent) : QWidget(parent), Qgameboard(new QBoard)
{
    std::cout <<  "show created" << std::endl;
    setPalette(QPalette(QColor(244, 239, 228)));
    setAutoFillBackground(true);

    pieceDisplay = new QLabel;
    pieceDisplay->setFrameStyle(QFrame::Box | QFrame::Raised);
    pieceDisplay->setAlignment(Qt::AlignVCenter);
    Qgameboard->setNext(pieceDisplay);

    scoreDisplay = new QLCDNumber(5);
    scoreDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *scorelabel = new QLabel(tr("SCORE:"));

    levelDisplay = new QLCDNumber(2);
    levelDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *levellabel = new QLabel(tr("LEVEL:"));

    linesDisplay = new QLCDNumber(5);
    linesDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *linelabel = new QLabel(tr("REMOVED LINES:"));

    QLabel *piecelabel = new QLabel(tr("NEXT PIECE:"));

    connect(Qgameboard, &QBoard::scoreChanged,
            scoreDisplay, qOverload<int>(&QLCDNumber::display));
    connect(Qgameboard, &QBoard::levelChanged,
            levelDisplay, qOverload<int>(&QLCDNumber::display));
    connect(Qgameboard, &QBoard::lineChanged,
            linesDisplay, qOverload<int>(&QLCDNumber::display));

    start = new QPushButton(tr("&Start"));
    start->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    start->setFocusPolicy(Qt::NoFocus);
    quit = new QPushButton(tr("&Quit"));
    quit->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    quit->setFocusPolicy(Qt::NoFocus);
    pause = new QPushButton(tr("&Pause"));
    pause->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    pause->setFocusPolicy(Qt::NoFocus);
    menu = new QPushButton(tr("&Menu"));
    menu->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    menu->setFocusPolicy(Qt::NoFocus);

    connect(start, &QPushButton::clicked, Qgameboard, &QBoard::start);
    connect(quit , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(pause, &QPushButton::clicked, Qgameboard, &QBoard::pause);
    connect(menu, &QPushButton::clicked, this, &Show::back);

    QVBoxLayout* left_layout = new QVBoxLayout;
    left_layout->addWidget(scorelabel);
    left_layout->addWidget(scoreDisplay);
    left_layout->addWidget(levellabel);
    left_layout->addWidget(levelDisplay);
    left_layout->addWidget(linelabel);
    left_layout->addWidget(linesDisplay);
    left_layout->addWidget(piecelabel);
    left_layout->addWidget(pieceDisplay);
    left_layout->addStretch(1);
    left_layout->addWidget(menu);
    left_layout->addWidget(start);
    left_layout->addWidget(pause);
    left_layout->addWidget(quit);

    QGridLayout *grid = new QGridLayout;
    grid->addLayout(left_layout,0,0);
    grid->addWidget(Qgameboard, 0,1,2,1);
    grid->setColumnStretch(1,20);
    setLayout(grid);

    setWindowTitle(tr("Tetris"));
    resize(485, 730);
}

void Show::back()
{
    Menu *gamemenu = new Menu;
    gamemenu->show();
    this->deleteLater();
}

Show::~Show()
{
    std::cout << "show destructed" << std::endl;
}


// Definition of a multi-show:

MultiShow::MultiShow(QWidget *parent) : QWidget(parent), Qgameboard(new MultiQBoard)
{
    std::cout <<  "multi show created" << std::endl;
    setPalette(QPalette(QColor(244, 239, 228)));
    setAutoFillBackground(true);

    pieceDisplay = new QLabel;
    pieceDisplay->setFrameStyle(QFrame::Box | QFrame::Raised);
    pieceDisplay->setAlignment(Qt::AlignVCenter);
    Qgameboard->setNext(pieceDisplay);

    myscoreDisplay = new QLCDNumber(5);
    myscoreDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *myscorelabel = new QLabel(tr("MY SCORE:"));

    opscoreDisplay = new QLCDNumber(5);
    opscoreDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *opscorelabel = new QLabel(tr("OPPONENT SCORE:"));

    levelDisplay = new QLCDNumber(2);
    levelDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *levellabel = new QLabel(tr("LEVEL:"));

    linesDisplay = new QLCDNumber(5);
    linesDisplay->setSegmentStyle(QLCDNumber::Filled);
    QLabel *linelabel = new QLabel(tr("REMOVED LINES:"));

    QLabel *piecelabel = new QLabel(tr("NEXT PIECE:"));

    connect(Qgameboard, &MultiQBoard::scoreChanged,
            myscoreDisplay, qOverload<int>(&QLCDNumber::display));
    connect(Qgameboard, &MultiQBoard::opscoreChanged,
            opscoreDisplay, qOverload<int>(&QLCDNumber::display));
    connect(Qgameboard, &MultiQBoard::levelChanged,
            levelDisplay, qOverload<int>(&QLCDNumber::display));
    connect(Qgameboard, &MultiQBoard::lineChanged,
            linesDisplay, qOverload<int>(&QLCDNumber::display));

    start = new QPushButton(tr("&Start"));
    start->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    start->setFocusPolicy(Qt::NoFocus);
    quit = new QPushButton(tr("&Quit"));
    quit->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    quit->setFocusPolicy(Qt::NoFocus);
    pause = new QPushButton(tr("&Pause"));
    pause->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    pause->setFocusPolicy(Qt::NoFocus);
    menu = new QPushButton(tr("&Menu"));
    menu->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    menu->setFocusPolicy(Qt::NoFocus);

    connect(start, &QPushButton::clicked, Qgameboard, &QBoard::start);
    connect(quit , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(pause, &QPushButton::clicked, Qgameboard, &QBoard::pause);
    connect(menu, &QPushButton::clicked, this, &MultiShow::back);

    QVBoxLayout* left_layout = new QVBoxLayout;
    left_layout->addWidget(myscorelabel);
    left_layout->addWidget(myscoreDisplay);
    left_layout->addWidget(levellabel);
    left_layout->addWidget(levelDisplay);
    left_layout->addWidget(linelabel);
    left_layout->addWidget(linesDisplay);
    left_layout->addWidget(piecelabel);
    left_layout->addWidget(pieceDisplay);
    left_layout->addWidget(opscorelabel);
    left_layout->addWidget(opscoreDisplay);
    left_layout->addStretch(1);
    left_layout->addWidget(menu);
    left_layout->addWidget(start);
    left_layout->addWidget(pause);
    left_layout->addWidget(quit);

    QGridLayout *grid = new QGridLayout;
    grid->addLayout(left_layout,0,0);
    grid->addWidget(Qgameboard, 0,1,2,1);
    grid->setColumnStretch(1,20);
    setLayout(grid);

    setWindowTitle(tr("Tetris"));
    resize(485, 730);
}

void MultiShow::back()
{
    Menu *gamemenu = new Menu;
    gamemenu->show();
    this->deleteLater();
}

MultiShow::~MultiShow()
{
    std::cout << "multi show destructed" << std::endl;
}
