#pragma once

#include <QWidget>

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
    Show(QWidget *parent = nullptr);
    ~Show();

private:
    QBoard *Qgameboard;
    QLabel *pieceDisplay;
    QLCDNumber *scoreDisplay;
    QLCDNumber *levelDisplay;
    QLCDNumber *linesDisplay;
    QPushButton *start;
    QPushButton *quit;
    QPushButton *pause;
};
