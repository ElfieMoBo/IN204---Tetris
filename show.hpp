#pragma once

#include "qboard.hpp"
#include <QWidget>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class QBoard;

class Show : public QWidget
{
    Q_OBJECT

public:
    QBoard *Qgameboard;

    Show(QWidget *parent = nullptr);
    ~Show();

public slots:
    void back();

protected:
    QLabel *pieceDisplay;
    QLCDNumber *scoreDisplay;
    QLCDNumber *levelDisplay;
    QLCDNumber *linesDisplay;
    QPushButton *start;
    QPushButton *quit;
    QPushButton *pause;
    QPushButton *menu;
};

class MultiShow : public QWidget
{
    Q_OBJECT
public:
    MultiQBoard *Qgameboard;

    MultiShow(QWidget * parent = nullptr);
    ~MultiShow();

public slots:
    void back();

protected:
    QLabel *pieceDisplay;
    QLCDNumber *myscoreDisplay;
    QLCDNumber *opscoreDisplay;
    QLCDNumber *levelDisplay;
    QLCDNumber *linesDisplay;
    QPushButton *start;
    QPushButton *quit;
    QPushButton *pause;
    QPushButton *menu;
};
