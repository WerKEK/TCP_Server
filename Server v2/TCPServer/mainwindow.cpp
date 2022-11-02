#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&server, &QTcpServer::newConnection, this, &MainWindow::handleNewConnection);


    createTable();

    ui->label_2->setText(QString::number(port));

    server.listen(QHostAddress::Any, port);

}

MainWindow::~MainWindow()
{   
    delete ui;
}

void MainWindow::handleNewConnection()
{
    socket = server.nextPendingConnection();
    sSockets.insert(socket);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::handleReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::handleDisconnected);

    fillTable();
}

void MainWindow::handleReadyRead()
{
    socket = (QTcpSocket*)sender();
    data = socket->readAll();
    fillTable();
}

void MainWindow::handleDisconnected()
{
    sSockets.remove((QTcpSocket*)sender()); //Удаляет последний зашедший сокет, а не тот, который отключился
    fillTable();
}


void MainWindow::fillTable()
{
    auto table = ui->tableWidget;
    table->clearContents();

    for (int i = 0; i < sSockets.size(); i++) {
        auto it = sSockets.begin() + i;
        table->insertRow(i);
        table->setItem(i, 0 ,new QTableWidgetItem((*it)->peerAddress().toString().remove("::ffff:")));
        table->setItem(i, 1 ,new QTableWidgetItem(QString::number((*it)->peerPort())));
        table->setItem(i, 2, new QTableWidgetItem(QString(data)));

        QPushButton* btn = new QPushButton("disconnect");
        connect(btn, &QPushButton::clicked, this, &MainWindow::handleDisconnectBtnClicked); //Как передать конкретную строчку и взять из неё конкретный сокет
        table->setCellWidget(i, 3, btn);
    }

    table->resizeColumnsToContents();
}


void MainWindow::handleDisconnectBtnClicked()
{
    int i = ui->tableWidget->currentRow();
    auto it = sSockets.begin() + i;
    sSockets.remove(*it);  //Работает не правильно, удаляется последний зашедший сокет
    fillTable();
}


void MainWindow::createTable()
{
    auto table = ui->tableWidget;
    table->clearContents();
    table->setColumnCount(4);
    table->setShowGrid(true);
    table->setHorizontalHeaderLabels(QStringList() << trUtf8("ip") <<trUtf8("port")<<trUtf8("last msg")<<trUtf8(""));
}
