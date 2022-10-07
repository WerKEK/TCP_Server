#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");

    createTable();

    server = new TCPServer();

    connect(server, &TCPServer::userCountChanged, this, &MainWindow::fillTable);

    ui->label_2->setText(QString::number(server->port));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    auto table = ui->tableWidget;
    table->setColumnCount(2);
    table->setShowGrid(true); // Включаем сетку
    table->setHorizontalHeaderLabels(QStringList() << trUtf8("ip") <<trUtf8("port"));
    table->resizeColumnsToContents();
}

void MainWindow::fillTable()
{
    auto table = ui->tableWidget;
    table->clear();
    createTable();

    for (int i = 0; i < server->vSockets.size(); i++) {
        if(server->vSockets[i] != nullptr){}
           table->insertRow(i);
           table->setItem(i,0, new QTableWidgetItem(server->vSockets[i]->peerAddress().toString().remove("::ffff:")));
           table->setItem(i,1, new QTableWidgetItem(QString::number(server->vSockets[i]->peerPort())));
    }

    table->resizeColumnsToContents();
}


void MainWindow::on_pushButton_deleteUser_clicked()
{
    if(server->socket != nullptr)
        server->socket->deleteLater();
}


void MainWindow::on_pushButton_updateTable_clicked()
{
    fillTable();
}

