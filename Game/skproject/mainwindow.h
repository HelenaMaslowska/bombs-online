#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QDataStream>
#include <QTimer>
#include <game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectToServer();
    void enableStartBtn();

private slots:
    void on_startBtn_clicked();
    void on_exitBtn_clicked();
    void read_data_from_server();
    void rdyYes();
    void rdyNo();
    void up();
    void down();
    void left();
    void right();
    void bomb();
    void backToStart();
    //void keyPressed();

    void on_confirmBtn_clicked();

private:
    Ui::MainWindow *ui;
    Game *game;
    QTcpSocket *TCPSocket;
    QString address = "127.0.0.1";
    int port = 8080;
    QTimer * timer;
    int status = 1;
};
#endif // MAINWINDOW_H
