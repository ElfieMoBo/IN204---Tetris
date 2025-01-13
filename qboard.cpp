#include "qboard.hpp"
#include "board.hpp"
#include "shape2D.hpp"

#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QColor>

Board gameboard;

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

    if(!gameboard.getGame()){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Game Over"));
        return;
    }

    if(menu){
        painter.drawText(rectangle, Qt::AlignCenter, tr("Press Start to begin"));
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
    qDebug() << "next";
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
        painter.setBrush(Qt::black);
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
    if(!gameboard.getWaiting() && !gameboard.getPause() && gameboard.getGame()){
        if(!gameboard.trymove(gameboard.getPiece(), gameboard.getX(), gameboard.getY() + 1)){
            gameboard.ndropped(0);
        }
        emit scoreChanged(gameboard.getScore());
        emit levelChanged(gameboard.getLevel());
        emit lineChanged(gameboard.getLines());
    }
    if(gameboard.getWaiting()){
        int time = (1000/(1 + gameboard.getLevel()));
        timer.start(time, this);
        gameboard.reverseWaiting();
    }
    if(!gameboard.getGame()){
        timer.stop();
    }
    update();
}

void QBoard::keyPressEvent(QKeyEvent * event)
{
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
            break;
        case Qt::Key_D:
            if(!gameboard.trymove(currentP, gameboard.getX(), gameboard.getY() + 1)){
                gameboard.ndropped(0);
            }
            break;
        default:
            QFrame::keyPressEvent(event);
        }
    } else {
        QFrame::keyPressEvent(event);
    }
}
