#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");

    createTable(); //Создаем таблицу

    server = new TCPServer(); //Создаем сервер

    connect(server, &TCPServer::userCountChanged, this, &MainWindow::fillTable); //При изменении кол-ва юзеров обновляем таблицу

    ui->label_2->setText(QString::number(server->port)); //Выводим порт, который слушает сервер
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    auto table = ui->tableWidget; //Просто сокращение записи
    table->setColumnCount(3); //Добавляем колонны
    table->setShowGrid(true); // Включаем сетку
    table->setHorizontalHeaderLabels(QStringList() << trUtf8("ip") <<trUtf8("port")<<trUtf8("")); //Даем имена колоннам
    table->resizeColumnsToContents(); //Автосайз по колонкам
}

void MainWindow::fillTable()
{
    auto table = ui->tableWidget; //Просто сокращение записи
    table->clear(); //Отчистка таблицы перед созданием
    createTable(); //Создание таблицы

    for (int i = 0; i < server->vSockets.size(); i++) {  //Заполнение таблицы из вектора сокетов
        if(server->vSockets[i] != nullptr){}
           table->insertRow(i); //Вставляем строчку
           table->setItem(i,0, new QTableWidgetItem(server->vSockets[i]->peerAddress().toString().remove("::ffff:"))); //Выводим айпи, при этом удаляя ненужные символы
           table->setItem(i,1, new QTableWidgetItem(QString::number(server->vSockets[i]->peerPort()))); //Выводим порт


           QPushButton* btn = new QPushButton("disconnect"); //Создаем кнопку
           connect(btn, &QPushButton::clicked, this, &MainWindow::disconnectUser_clicked); //Коннектим, при клике вызываем слот удаления юзера
           table->setCellWidget(i,2, btn); //Вставка кнопки в таблицу
    }

    table->resizeColumnsToContents(); //Автосайз по колоннам
}


void MainWindow::disconnectUser_clicked(int i)
{
    server->vSockets.at(i)->deleteLater(); //Удаление юзера
}


