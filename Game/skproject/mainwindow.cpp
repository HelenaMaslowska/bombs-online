#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game = new Game();
    //timer = new QTimer();
    //connect(timer,&QTimer::timeout,this,&MainWindow::changeWindow);
    //timer->start(1000); // 1000 ms

    TCPSocket = new QTcpSocket();
    //TCPSocket->connectToHost(QHostAddress(127.0.0.1), 8080);
    TCPSocket->connectToHost(QHostAddress::LocalHost, 8080);
    connect(TCPSocket,SIGNAL(readyRead()), this, SLOT(read_data_from_server()));
    TCPSocket->open(QIODevice::ReadWrite);
//    if (TCPSocket->isOpen())
//    {
//        QMessageBox::information(this, "Hej! Miłego kodowania!", "Połączyłaś się ez");
//    }
//    else
//    {
//        QMessageBox::information(this, "Nie dziala xd", "nie polaczylas sie ez");
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startBtn_clicked()
{
    if (TCPSocket)
    {
        QString WriteData = ui->nickInput->text();
        if (TCPSocket->isOpen())
        {
            TCPSocket->write(WriteData.toStdString().c_str());
            game->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(this, "Hej! Miłego debugowania!", TCPSocket->errorString());
        }
    }
    else
    {
        QMessageBox::information(this, "Hej! Miłego debugowania!", TCPSocket->errorString());
    }
}

void MainWindow::on_exitBtn_clicked()
{
    this->close();
}

void MainWindow::read_data_from_server()
{
    if (TCPSocket)
    {
        if (TCPSocket->isOpen())
        {
            QByteArray data_from_server = TCPSocket->readAll();
            //QDataStream DataIn(&data_from_server, QIODevice::ReadOnly);
            //DataIn.setVersion(QDataStream::Version::Qt_5_15);

            QString MessageString = QString::fromStdString(data_from_server.toStdString());
            //while (DataIn.atEnd() == false)
            //{
            //    DataIn >> MessageString;
            //}
            ui->nickInput->setText(MessageString);  //zamiast setText append
        }
    }
}






















