#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QtNetwork>
#include <QDoubleSpinBox>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    void sending(const QString &message, QObject *sender);
    ~Server();

private slots:
    void connection();
    void data();
    void deconnection();

public slots:
    void creating();
    void connecting();
    void deleting();
    void back();

private:
    QLineEdit *IPserver;
    QDoubleSpinBox *portserver;
    QPushButton *connectionbutton;
    QPushButton *creatingserver;
    QPushButton *menu;
    QVBoxLayout *left_layout;
    QGridLayout *grid;

    QTcpServer *myserver;
    QList<QTcpSocket*> guests;
    quint16 size;

};
