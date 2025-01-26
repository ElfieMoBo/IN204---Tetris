#include "server.hpp"
#include "menu.hpp"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <iostream>

Server::Server(QWidget *parent) : QWidget(parent)
{
    std::cout <<  "server created" << std::endl;
    // displaying the choice:
    setPalette(QPalette(QColor(244, 239, 228)));
    setAutoFillBackground(true);

    IPserver = new QLineEdit(tr("&localhost"));
    IPserver->setStyleSheet((QString)"QLineEdit {background-color: #fdfaf3}");
    IPserver->setFocusPolicy(Qt::ClickFocus);
    QLabel *ip = new QLabel(tr("Server's IP:"));

    portserver = new QDoubleSpinBox();
    portserver->setMaximum(100000);
    portserver->setDecimals(0);
    portserver->setStyleSheet((QString)"QLineEdit {background-color: #fdfaf3}");
    portserver->setFocusPolicy(Qt::ClickFocus);
    QLabel *port = new QLabel(tr("Server's port:"));

    connectionbutton = new QPushButton(tr("Join a loby"));
    connectionbutton->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    connectionbutton->setFocusPolicy(Qt::NoFocus);
    creatingserver = new QPushButton(tr("Create a loby"));
    creatingserver->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    creatingserver->setFocusPolicy(Qt::NoFocus);
    menu = new QPushButton(tr("&Menu"));
    menu->setStyleSheet((QString)"QPushButton {background-color: #fdfaf3}");
    menu->setFocusPolicy(Qt::NoFocus);

    connect(connectionbutton, &QPushButton::clicked, this, &Server::connecting);
    connect(creatingserver, &QPushButton::clicked, this, &Server::creating);
    connect(menu, &QPushButton::clicked, this, &Server::back);


    left_layout = new QVBoxLayout;
    left_layout->addWidget(ip);
    left_layout->addWidget(IPserver);
    left_layout->addWidget(port);
    left_layout->addWidget(portserver);
    left_layout->addWidget(connectionbutton);
    left_layout->addWidget(creatingserver);
    left_layout->addWidget(menu);

    grid = new QGridLayout;
    grid->addLayout(left_layout,0,0);
    setLayout(grid);

    setWindowTitle(tr("Tetris : player 1"));
    resize(100, 100);
}

void Server::connection()
{
    QTcpSocket *newguest = myserver->nextPendingConnection();
    guests << newguest;
    connect(newguest, SIGNAL(readyRead()), this, SLOT(data()));
    connect(newguest, SIGNAL(disconnected()), this, SLOT(deconnection()));
}
void Server::data()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(socket==0) // ie cast doesn't function
        return;

    QDataStream in(socket);
    if(size==0){ // not enough place to have the size of the message
        if(socket->bytesAvailable()<(int)sizeof(quint16))
            return;
        in >> size;
    }
    if(socket->bytesAvailable() < size)
        return;

    QString message;
    in >> message;

    sending(message, sender());
    size = 0;
}

void Server::deconnection()
{
    sending(tr("mplayer"), sender());
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(socket == 0)
        return;
    guests.removeOne(socket);
    socket->deleteLater();
}

void Server::sending(const QString &message, QObject* sender)
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) 0; // reservation for the size
    out << message;
    out.device()->seek(0); // back to the begining
    out << (quint16) (packet.size()-sizeof(quint16));

    for(int i=0; i<guests.size(); i++){
        if(guests[i] != qobject_cast<QTcpSocket*>(sender))
            guests[i]->write(packet);
    }
}

void Server::creating()
{
    myserver = new QTcpServer;
    if(!myserver->listen(QHostAddress::Any, portserver->value())){
        std::cout << "server could not be launched" << std::endl;
    } else {
        connect(myserver, SIGNAL(newConnection()), this, SLOT(connection()));
    }
    size = 0;
    MultiShow *game = new MultiShow;
    game->Qgameboard->setHost("localhost");
    game->Qgameboard->setPort(portserver->value());
    game->Qgameboard->connecting();
    game->Qgameboard->setKeys(true);
    game->show();
    this->hide();
}
void Server::connecting()
{
    MultiShow *game = new MultiShow;
    game->Qgameboard->setHost(IPserver->text());
    game->Qgameboard->setPort(portserver->value());
    game->Qgameboard->connecting();
    game->Qgameboard->plusplayers();
    game->Qgameboard->setKeys(false);
    game->show();
    this->hide();
}
void Server::back()
{
    Menu *gamemenu = new Menu;
    gamemenu->show();
    this->deleteLater();
}

void Server::deleting()
{
    this->deleteLater();
}

Server::~Server()
{
    delete IPserver;
    delete portserver;
    delete connectionbutton;
    delete creatingserver;
    delete menu;
    delete left_layout;
    delete grid;
    std::cout << "server destructed" << std::endl;
}
