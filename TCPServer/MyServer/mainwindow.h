#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpserver.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    TCPServer *server;

    void createTable();

private slots:
    void disconnectUser_clicked(int i);

    void fillTable();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
