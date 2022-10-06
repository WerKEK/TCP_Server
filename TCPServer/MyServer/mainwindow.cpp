#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->label_2->setText(QString::number(server.port));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_deleteUser_clicked()
{
    for (auto s : server.vSockets) {
        if(s != nullptr)
            ui->textBrowser->append(s->readAll());
    }
}


void MainWindow::on_pushButton_updateTable_clicked()
{
    if(server.socket != nullptr)
        server.socket->disconnect();
}

