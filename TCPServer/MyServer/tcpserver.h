#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    TCPServer();
    QTcpSocket* socket;
    QVector<QTcpSocket*> vSockets;
    int port = 5555;


public slots:
    void incomingConnection(qintptr socketDescription);
    void disconnectSocket();
    void slotReadyRead();

};

#endif // TCPSERVER_H
