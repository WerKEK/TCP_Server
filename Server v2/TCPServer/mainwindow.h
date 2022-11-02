#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTcpServer server;
    QSet<QTcpSocket*> sSockets;
    QTcpSocket* socket;


    int port = 5555;

    QByteArray data;

    void fillTable();
    void createTable();


private slots:
    void handleNewConnection();
    void handleReadyRead();
    void handleDisconnected();
    void handleDisconnectBtnClicked();

};
#endif // MAINWINDOW_H
