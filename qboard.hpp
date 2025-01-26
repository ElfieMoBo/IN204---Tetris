#pragma once

#include <QFrame>
#include <QBasicTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QtNetwork>

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

    protected:
        QBasicTimer timer;
        int nlines;
        QLabel *nextpiecelabel = new QLabel();
        bool menu;

    public slots:
        virtual void start();
        virtual void pause();

    signals:
        void scoreChanged(int score);
        void levelChanged(int level);
        void lineChanged(int numLines);

    protected:
        virtual void paintEvent(QPaintEvent *event) override;
        virtual void keyPressEvent(QKeyEvent *event) override;
        virtual void timerEvent(QTimerEvent *event) override;
};

class MultiQBoard : public QBoard
{
    Q_OBJECT

public:
    MultiQBoard(QWidget *parent = nullptr);
    ~MultiQBoard(){};

    void setHost(QString newhostname){ hostname = newhostname; }
    void setPort(quint16 newport){ portserver = newport; }
    void setKeys(bool isarrows){ arrows = isarrows; }
    void plusplayers(){ players ++; }

protected:
    QBasicTimer timer;
    int nlines;
    QLabel *nextpiecelabel = new QLabel();

    QTcpSocket *socket;
    QString hostname;
    quint16 portserver;
    quint16 lenghtmessage;
    int players;
    bool bothplaying;
    bool arrows;
    bool menu;

public slots:
    void start() override;
    void pause() override;
    void connecting();

private slots:
    void allyligne();
    void lose();
    void oppositeinformation();
    void deconnected();
    void connected();
    void play();
    void mypause();
    void myplay();
    void myscore();
    void opponentkey(int key);

signals:
    void opscoreChanged(int score);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
};
