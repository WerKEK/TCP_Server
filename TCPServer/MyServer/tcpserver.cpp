#include "tcpserver.h"
#include <algorithm>



TCPServer::TCPServer()
{
    if(this->listen(QHostAddress::Any, port)) //При создании сервера сразу слушаем порт 5555
        qDebug()<<"started";
    else
        qDebug()<<"error";
}

void TCPServer::incomingConnection(qintptr socketDescription) //При входящем соединении создаем новый сокет
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescription); //Устанавливаем ему дескриптор

    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::slotReadyRead); //Коннектим методы и сигналы
    connect(socket, &QTcpSocket::disconnected, this, &TCPServer::disconnectSocket);

    vSockets.push_back(socket); //Добавляем этот сокет в вектор сокетов для последующей выгрузки

    emit userCountChanged(); //Отправляем сигнал, что кол-во юзеров на сервере изменилось
}

void TCPServer::disconnectSocket()
{
    auto res = std::find(vSockets.begin(),vSockets.end(), socket); //Ищем итератор конкретного сокета
    vSockets.erase(res);   //Удаляем его из вектора сокетов

    socket->deleteLater();//Удаляем сокет

    emit userCountChanged();//Отправляем сигнал, что кол-во юзеров на сервере изменилось
}

void TCPServer::slotReadyRead()
{
    qDebug() << "reading...";
}
