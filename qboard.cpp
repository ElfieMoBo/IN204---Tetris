#include "qboard.hpp"
#include "board.hpp"
#include "shape2D.hpp"
#include "menu.hpp"

#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QColor>

MultiBoard gameboard;

QBoard::QBoard(QWidget *parent) : QFrame(parent)
{
    menu = true;
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    gameboard.clearboard();
    gameboard.newpiece();
}

void QBoard::start()
{
    gameboard.clearboard();
    gameboard.setScore(0);
    gameboard.setLevel(1);
    gameboard.setLines(0);
    gameboard.Game();
    emit scoreChanged(gameboard.getScore());
    emit levelChanged(gameboard.getLevel());
    emit lineChanged(gameboard.getLines());
    timer.start(500, this);
    gameboard.newpiece();
    menu = false;
    update();
}
void QBoard::pause()
{
    gameboard.reversePause();
}

void QBoard::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rectangle = contentsRect();

    if(gameboard.getPause()){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Pause"));
        return;
    }
    if(menu){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Press Start to begin"));
        return;
    }
    if(gameboard.getVictory()){
        painter.drawText(rectangle, Qt::AlignCenter, tr("You win !"));
        return;
    }
    if(!gameboard.getGame()){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Game Over"));
        return;
    }

    paintBoard(painter);
}

void QBoard::paintBoard(QPainter &painter)
{
    painter.setPen(Qt::black);
    std::vector<int> boardtoshow = gameboard.getBoard();
    auto start = boardtoshow.begin();
    auto last = boardtoshow.end();
    int line = 0;
    int column = 0;
    int size = 35;
    while(start != last){
        if(line%10==0 && line!=0){
            line = 0;
            column ++;
        }
        int k = *start;
        painter.translate(35*line,35*column);
        painter.drawRect(paintSquare(size, k, painter));
        painter.translate(-35*line, -35*column);
        start ++;
        line ++;
    }
    paintTetrimino(painter);
    paintNext();
}

void QBoard::paintTetrimino(QPainter &painter) const
{
    painter.setPen(Qt::black);
    int k = gameboard.getPiece().getShape();
    int o = gameboard.getPiece().getOrientation();
    int x = gameboard.getX();
    int y = gameboard.getY();
    int size = 35;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(PIECE[k][o][i][j]!=0){
                painter.translate(size*(x+i),size*(y+j));
                painter.drawRect(paintSquare(size, k, painter));
                painter.translate(-size*(x+i), -size*(y+j));
            }
        }
    }
}

void QBoard::paintNext()
{
    Piece next = gameboard.getNextPiece();
    int k = next.getShape();
    int o = next.getOrientation();
    int size = 25;
    QPixmap pixmap(4*size + 2,4*size + 2);
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextpiecelabel->palette().window());
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(PIECE[k][o][i][j]==1){
                painter.translate(1 + size*(i), 1 +size*(j));
                painter.drawRect(paintSquare(size, k , painter));
                painter.translate(-1 -size*(i), -1 -size*(j));
            }
        }
    }
    nextpiecelabel->setPixmap(pixmap);
}

QRect QBoard::paintSquare(int size, int k, QPainter &painter) const
{
    QColor color;
    switch(k)
    {
    case 0: // cyan
        color.setRgb(166, 228, 230);
        painter.setBrush(color);
        break;
    case 1: // blue
        color.setRgb(168, 212, 253);
        painter.setBrush(color);
        break;
    case 2: // orange
        color.setRgb(244, 210, 153);
        painter.setBrush(color);
        break;
    case 3: // yellow
        color.setRgb(253, 236, 168);
        painter.setBrush(color);
        break;
    case 4: // green
        color.setRgb(206, 235, 165);
        painter.setBrush(color);
        break;
    case 5: // purple
        color.setRgb(187, 181, 233);
        painter.setBrush(color);
        break;
    case 6: // red
        color.setRgb(239, 185, 227);
        painter.setBrush(color);
        break;
    case 9: // terre
        color.setRgb(155, 117, 33);
        painter.setBrush(color);
        break;
    default:
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::transparent);
        break;
    }
    QRect result(QRect(0,0,size,size));
    return result;
}

void QBoard::timerEvent(QTimerEvent *event)
{
    int previousline = gameboard.getLines();
    if(!gameboard.getWaiting() && !gameboard.getPause() && gameboard.getGame()){
        if(!gameboard.trymove(gameboard.getPiece(), gameboard.getX(), gameboard.getY() + 1)){
            gameboard.ndropped(0);
        }
        emit scoreChanged(gameboard.getScore());
        emit levelChanged(gameboard.getLevel());
        if(previousline != gameboard.getLines()){
            emit lineChanged(gameboard.getLines());
        }
    }
    if(gameboard.getWaiting()){
        int time = (1000/(1 + gameboard.getLevel()));
        timer.start(time, this);
        gameboard.reverseWaiting();
    }
    if(!gameboard.getGame()){
        timer.stop();
    }
    else {
        QFrame::timerEvent(event);
    }
    update();
}

void QBoard::keyPressEvent(QKeyEvent * event)
{
    int previousline = gameboard.getLines();
    if(gameboard.getGame()){
        Piece currentP = gameboard.getPiece();
        switch (event->key()) {
        case Qt::Key_Left:
            gameboard.trymove(currentP, gameboard.getX() - 1, gameboard.getY());
            break;
        case Qt::Key_Right:
            gameboard.trymove(currentP, gameboard.getX() + 1, gameboard.getY());
            break;
        case Qt::Key_Down:
            gameboard.trymove(currentP.rotateR(), gameboard.getX(), gameboard.getY());
            break;
        case Qt::Key_Up:
            gameboard.trymove(currentP.rotateL(), gameboard.getX(), gameboard.getY());
            break;
        case Qt::Key_Space:
            gameboard.drop();
            if(previousline != gameboard.getLines()){
                emit lineChanged(gameboard.getLines());
            }
            break;
        case Qt::Key_Exclam:
            gameboard.movedown();
            if(previousline != gameboard.getLines()){
                emit lineChanged(gameboard.getLines());
            }
            break;
        default:
            QFrame::keyPressEvent(event);
        }
    }
}

// Definition of a MultiQBoard

// Override functions:

MultiQBoard::MultiQBoard(QWidget *parent) : QBoard(parent)
{
    menu = true;
    bothplaying = false;
    arrows = true;
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(oppositeinformation()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnected()));
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    gameboard.clearboard();
    gameboard.newpiece();
    lenghtmessage = 0;
}

void MultiQBoard::start()
{
    gameboard.clearboard();
    gameboard.setScore(0);
    gameboard.setLevel(1);
    gameboard.setLines(0);
    if(players!=1){
        gameboard.Game();
        emit scoreChanged(gameboard.getScore());
        emit opscoreChanged(0);
        emit levelChanged(gameboard.getLevel());
        emit lineChanged(gameboard.getLines());
        timer.start(500, this);
        gameboard.newpiece();
        menu = false;
        gameboard.Game();
        gameboard.setVictory(false);
    }
    play();
    update();
}
void MultiQBoard::pause()
{
    if(gameboard.getPause()){ myplay(); }
    else { mypause(); }
    gameboard.reversePause();
}

void MultiQBoard::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rectangle = contentsRect();


    if(gameboard.getPause()){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Pause"));
        return;
    }
    if(players==1){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Waiting for an opponent"));
        emit scoreChanged(0);
        emit opscoreChanged(0);
        emit levelChanged(0);
        emit lineChanged(0);
        return;
    }
    if(menu){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Press Start to begin"));
        return;
    }
    if(gameboard.getVictory()){
        painter.drawText(rectangle, Qt::AlignCenter, tr("You win !"));
        return;
    }
    if(!gameboard.getGame()){
        lose();
        painter.drawText(rectangle, Qt::AlignCenter, tr("Game Over"));
        return;
    }

    paintBoard(painter);
}

void MultiQBoard::keyPressEvent(QKeyEvent * event)
{
    int previousline = gameboard.getLines();
    if(gameboard.getGame()){
        Piece currentP = gameboard.getPiece();
        if(arrows){
            switch (event->key()) {
            case Qt::Key_Left:
                gameboard.trymove(currentP, gameboard.getX() - 1, gameboard.getY());
                break;
            case Qt::Key_Right:
                gameboard.trymove(currentP, gameboard.getX() + 1, gameboard.getY());
                break;
            case Qt::Key_Down:
                gameboard.trymove(currentP.rotateR(), gameboard.getX(), gameboard.getY());
                break;
            case Qt::Key_Up:
                gameboard.trymove(currentP.rotateL(), gameboard.getX(), gameboard.getY());
                break;
            case Qt::Key_Space:
                gameboard.drop();
                if(previousline != gameboard.getLines()){
                    emit lineChanged(gameboard.getLines());
                    if(gameboard.gettwolines()){
                        allyligne();
                    }
                }
                break;
            case Qt::Key_Exclam:
                gameboard.movedown();
                if(previousline != gameboard.getLines()){
                    emit lineChanged(gameboard.getLines());
                    if(gameboard.gettwolines()){
                        allyligne();
                    }
                }
                break;
            // sending key pressed to the other player
            case Qt::Key_D: //right
                opponentkey(1);
                break;
            case Qt::Key_Q: //left
                opponentkey(2);
                break;
            case Qt::Key_S: //rotate right
                opponentkey(3);
                break;
            case Qt::Key_Z: //rotate left
                opponentkey(4);
                break;
            case Qt::Key_X: //hard drop
                opponentkey(5);
                break;
            case Qt::Key_E: //just one line
                opponentkey(6);
                break;
            default:
                QFrame::keyPressEvent(event);
            }
        } else if(!arrows) {
            switch (event->key()) {
            case Qt::Key_Q:
                gameboard.trymove(currentP, gameboard.getX() - 1, gameboard.getY());
                break;
            case Qt::Key_D:
                gameboard.trymove(currentP, gameboard.getX() + 1, gameboard.getY());
                break;
            case Qt::Key_S:
                gameboard.trymove(currentP.rotateR(), gameboard.getX(), gameboard.getY());
                break;
            case Qt::Key_Z:
                gameboard.trymove(currentP.rotateL(), gameboard.getX(), gameboard.getY());
                break;
            case Qt::Key_X:
                gameboard.drop();
                if(previousline != gameboard.getLines()){
                    emit lineChanged(gameboard.getLines());
                    if(gameboard.gettwolines()){
                        allyligne();
                    }
                }
                break;
            case Qt::Key_E:
                gameboard.movedown();
                if(previousline != gameboard.getLines()){
                    emit lineChanged(gameboard.getLines());
                    if(gameboard.gettwolines()){
                        allyligne();
                    }
                }
                break;
            // sending key pressed to the other player
            case Qt::Key_Right: //right
                opponentkey(1);
                break;
            case Qt::Key_Left: //left
                opponentkey(2);
                break;
            case Qt::Key_Down: //rotate right
                opponentkey(3);
                break;
            case Qt::Key_Up: //rotate left
                opponentkey(4);
                break;
            case Qt::Key_Space: //hard drop
                opponentkey(5);
                break;
            case Qt::Key_Exclam:
                opponentkey(6);
                break;
            default:
                QFrame::keyPressEvent(event);
            }
        }
    }
    if(!gameboard.getGame()){
        lose();
        timer.stop();
    }
}

void MultiQBoard::timerEvent(QTimerEvent *event)
{
    int previousline = gameboard.getLines();
    if(!gameboard.getWaiting() && !gameboard.getPause() && gameboard.getGame()){
        if(!gameboard.trymove(gameboard.getPiece(), gameboard.getX(), gameboard.getY() + 1)){
            gameboard.ndropped(0);
        }
        emit scoreChanged(gameboard.getScore());
        myscore();
        emit levelChanged(gameboard.getLevel());
        if(previousline != gameboard.getLines()){
            emit lineChanged(gameboard.getLines());
            if(gameboard.gettwolines()){
                allyligne();
            }
        }
    }
    if(gameboard.getWaiting()){
        int time = (1000/(1 + gameboard.getLevel()));
        timer.start(time, this);
        gameboard.reverseWaiting();
    }
    if(!gameboard.getGame()){
        //lose();
        timer.stop();
    }
    else {
        QFrame::timerEvent(event);
    }
    update();
}

// Sending or receiving messages to the other players:

void MultiQBoard::connecting()
{
    qDebug() << "connecting";
    socket->abort();
    socket->connectToHost(hostname,portserver);
}
void MultiQBoard::connected()
{
    qDebug() << "connected !";
}
void MultiQBoard::deconnected()
{
    lose();
    qDebug() << "Disconnected...";
    players = 1;
    gameboard.endGame();
}
void MultiQBoard::allyligne()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    QString message = tr("line");
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}
void MultiQBoard::myscore()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    int score = gameboard.getScore();
    QString message = QString::number(score);
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}
void MultiQBoard::oppositeinformation()
{
    if(players==1){
        players ++;
    }
    QDataStream in(socket);
    if(lenghtmessage==0){
        if(socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> lenghtmessage;
    }

    if(socket->bytesAvailable() < lenghtmessage)
        return;
    QString message;
    in >> message;
    qDebug() << "message received :";
    qDebug() << message;
    int previousline = gameboard.getLines();
    if(message=="line"){
        gameboard.plusopponentline();
    } else if(message=="uwin"){
        gameboard.setVictory(true);
        gameboard.endGame();
    } else if(message=="mplayer"){
        players --;
        gameboard.setVictory(true);
        gameboard.endGame();
        players = 1;
    } else if(message=="play" && !gameboard.getGame()){
        start();
    } else if(message=="pause" && !gameboard.getPause()){
        gameboard.reversePause();
    } else if(message=="replay" && gameboard.getPause()){
        gameboard.reversePause();
    } else if(message=="right"){
        Piece currentP = gameboard.getPiece();
        gameboard.trymove(currentP, gameboard.getX() + 1, gameboard.getY());
    } else if(message=="left"){
        Piece currentP = gameboard.getPiece();
        gameboard.trymove(currentP, gameboard.getX() - 1, gameboard.getY());
    }else if(message=="rotateR"){
        Piece currentP = gameboard.getPiece();
        gameboard.trymove(currentP.rotateR(), gameboard.getX(), gameboard.getY());
    }else if(message=="rotateL"){
        Piece currentP = gameboard.getPiece();
        gameboard.trymove(currentP.rotateL(), gameboard.getX(), gameboard.getY());
    }else if(message=="harddrop"){
        gameboard.drop();
        if(previousline != gameboard.getLines()){
            emit lineChanged(gameboard.getLines());
            if(gameboard.gettwolines()){
                allyligne();
            }
        }
    }
    else if(message=="movedown"){
        gameboard.movedown();
        if(previousline != gameboard.getLines()){
            emit lineChanged(gameboard.getLines());
            if(gameboard.gettwolines()){
                allyligne();
            }
        }
    } else {
        emit opscoreChanged(QVariant(message).toInt());
    }

    lenghtmessage = 0;
}
void MultiQBoard::lose()
{
    qDebug() << "sending lose";
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    QString message = tr("uwin");
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}
void MultiQBoard::play()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    QString message = tr("play");
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}
void MultiQBoard::mypause()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    QString message = tr("pause");
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}
void MultiQBoard::myplay()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    QString message = tr("replay");
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}


void MultiQBoard::opponentkey(int key)
{ // Or else, I can't play on both game on the same screen
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    QString message;
    switch(key)
    {
    case 1:
       message = tr("right");
        break;
    case 2:
        message = tr("left");
        break;
    case 3:
        message = tr("rotateR");
        break;
    case 4:
        message = tr("rotateL");
        break;
    case 5:
        message = tr("harddrop");
        break;
    case 6:
        message = tr("movedown");
        break;
    default:
        message = tr("nothing");
        break;
    }
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(paquet.size()-sizeof(quint16));

    socket->write(paquet);
}
