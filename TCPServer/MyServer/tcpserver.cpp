#include "tcpserver.h"
#include <algorithm>


TCPServer::TCPServer()
{
    if(this->listen(QHostAddress::Any, port))
        qDebug()<<"started";
    else
        qDebug()<<"error";
}

void TCPServer::incomingConnection(qintptr socketDescription)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescription);

    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPServer::disconnectSocket);

    vSockets.push_back(socket);
    qDebug() << "Connected new user: " << socketDescription;
}

void TCPServer::disconnectSocket()
{
    auto res = std::find(vSockets.begin(),vSockets.end(), socket);
    vSockets.erase(res);


    socket->deleteLater();
    qDebug() << "user disconnected";
}

void TCPServer::slotReadyRead()
{
    qDebug() << "reading...";
}
