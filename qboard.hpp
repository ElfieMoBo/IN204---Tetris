#pragma once

#include <QFrame>
#include <QBasicTimer>
#include <QKeyEvent>
#include <QLabel>

class QBoard : public QFrame
{
    Q_OBJECT

    public:
        QBoard(QWidget *parent = NULL);
        ~QBoard(){}

        void paintBoard(QPainter &painter);
        void paintTetrimino(QPainter &painter) const;
        QRect paintSquare(int size, int color, QPainter &painter) const;
        void paintNext();
        void setNext(QLabel *label){
            nextpiecelabel = label;
        };

    private:
        QBasicTimer timer;
        int oldscore;
        int oldlevel;
        int oldlines;
        bool menu;
        QLabel *nextpiecelabel = new QLabel();

    public slots:
        void start();
        void pause();

    signals:
        void scoreChanged(int score);
        void levelChanged(int level);
        void lineChanged(int numLines);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void timerEvent(QTimerEvent *event) override;
};
