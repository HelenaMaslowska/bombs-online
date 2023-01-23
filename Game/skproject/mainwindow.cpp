#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
    TCPSocket = new QTcpSocket();
    TCPSocket->connectToHost(QHostAddress::LocalHost, 8080); //TCPSocket->connectToHost(QHostAddress(127.0.0.1), 8080);
    connect(TCPSocket,SIGNAL(readyRead()), this, SLOT(read_data_from_server()));
    TCPSocket->open(QIODevice::ReadWrite);
//    if (TCPSocket->isOpen()) { QMessageBox::information(this, "Hej! Miłego kodowania!", "Połączyłaś się ez"); }
}
MainWindow::~MainWindow() { delete ui; }

/*
 * When you click startBtn then MainWindow send nickname to the server.
 * Example: user"Nick name1"       -  "user": prefix, "Nick name1": player's input
 * Show new window and hide start menu. Set nickname in game.
 */
void MainWindow::on_startBtn_clicked() // send nickname to the server
{
    //if (TCPSocket)
    if (TCPSocket->isOpen())
    {
        QString prefix = "user\"";
        QString nick = (ui->nickInput->text());
        if(nick.size() > 15) nick = nick.sliced(0,15);
        QString sendMessage = prefix + nick + "\"";
        TCPSocket->write(sendMessage.toStdString().c_str());
        game->setNickname(nick);
        game->show();
        this->hide();
    }
    else { QMessageBox::information(this, "Hej! Miłego debugowania!", TCPSocket->errorString()); }
}

/*
 * Exit using exitBtn.
 */
void MainWindow::on_exitBtn_clicked()
{
    this->close();
}

/*
 * Read data from server at once.
 * TODO
 * - when server will be done: read data and wait for every piece of package
 */
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
            ui->nickInput->setText(MessageString);
        }
    }
}






















