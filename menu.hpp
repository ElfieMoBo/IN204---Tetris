#pragma once

#include "show.hpp"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = NULL);
    ~Menu();
public slots:
    void solo();
    void multi();
    void setKill(bool iskill){
        tokill = iskill;
    }

private:
    QPushButton *solobutton;
    QPushButton *multibutton;
    QPushButton *quit;
    bool tokill;
};
