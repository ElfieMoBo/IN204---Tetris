#include "show.hpp"
#include "qboard.hpp"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

#include "iostream"

Show::Show(QWidget *parent) : QWidget(parent), Qgameboard(new QBoard)
{
    setPalette(QPalette(QColor(244, 239, 228)));
    setAutoFillBackground(true);

    pieceDisplay = new QLabel;
    pieceDisplay->setFrameStyle(QFrame::Box | QFrame::Raised);
    pieceDisplay->setAlignment(Qt::AlignCenter);
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

    connect(start, &QPushButton::clicked, Qgameboard, &QBoard::start);
    connect(quit , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(pause, &QPushButton::clicked, Qgameboard, &QBoard::pause);


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
    left_layout->addWidget(start);
    left_layout->addWidget(pause);
    left_layout->addWidget(quit);

    QGridLayout *grid = new QGridLayout;
    grid->addLayout(left_layout,0,0);
    grid->addWidget(Qgameboard, 0,1,2,1);
    grid->setColumnStretch(1,20);
    setLayout(grid);

    setWindowTitle(tr("Tetris"));
    resize(495, 730);
}


Show::~Show()
{
    std::cout << "Destruction !" << std::endl;
}
