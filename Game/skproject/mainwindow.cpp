#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
    TCPSocket = new QTcpSocket();
    TCPSocket->connectToHost(QHostAddress::LocalHost, 8080);
    connect(TCPSocket,SIGNAL(readyRead()), this, SLOT(read_data_from_server()));
    connect(game, SIGNAL(keyboardUp()), this, SLOT(read_data_from_server()));
    connect(game, SIGNAL(keyboardDown()), this, SLOT(keyPressedDown()));
    connect(game, SIGNAL(keyboardLeft()), this, SLOT(keyPressedLeft()));
    connect(game, SIGNAL(keyboardRight()), this, SLOT(keyPressedRight()));

    //connect(TCPSocket, SIGNAL(bytesWritten(qint64)),this->game, SLOT(send_data_to_server())); //doesnt work
    TCPSocket->open(QIODevice::ReadWrite);
//    if (TCPSocket->isOpen()) { QMessageBox::information(this, "Hej! Miłego kodowania!", "Połączyłaś się ez"); }
}
MainWindow::~MainWindow() {
    if(TCPSocket) TCPSocket->close();
    delete ui;
}

/*
 * When you click startBtn then MainWindow send nickname to the server.
 * Example: nick;Nick name;       -  "nick": prefix, "Nick name": player's input, ";": separator
 * Show new window and hide start menu. Set nickname in game.
 */
void MainWindow::on_startBtn_clicked() // send nickname to the server
{
    //if ()
    if (TCPSocket && TCPSocket->isOpen())
    {
        QString prefix = "nick;";
        QString nick = (ui->nickInput->text());
        if(nick.size() > 15) nick = nick.sliced(0,15);
        QString sendMessage = prefix + nick + ";";
        TCPSocket->write(sendMessage.toStdString().c_str());
        game->setNickname(nick);
        game->show();
        //this->hide();
        this->status = 2;
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

//void MainWindow::keyPressedUp()
//{
//    if (TCPSocket && TCPSocket->isOpen())
//    {
//        TCPSocket->write("!;up;?");
//    }
//}

/*
 * Read and send data from server at once.
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
            //while (DataIn.atEnd() == false) { DataIn >> MessageString; }

            ui->nickInput->setText(MessageString);
            if (this->status <= 2 && MessageString.split(";")[1] == "map")
            {
                game->mapNumber = MessageString.split(";")[2];
            }
            game->serverData(MessageString);
            //game->setNicksOnTheRight(MessageString);
            MessageString = "";

            if(game->exit)
            {
                TCPSocket->write("!;exit;?");
                game->exit == false;
            }

            if (this->status == 2)
            {
                if (game->ready)
                {
                    QString sendMessage = "!;rdy;1;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
                else if(!game->ready)
                {
                    QString sendMessage = "!;rdy;0;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
            }
            if(this->status == 3)
            {
                if(game->move == "u")
                {
                    QString sendMessage = "!;go;u;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
                if(game->move == "d")
                {
                    QString sendMessage = "!;go;d;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
                if(game->move == "l")
                {
                    QString sendMessage = "!;go;l;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
                if(game->move == "r")
                {
                    QString sendMessage = "!;go;r;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
                if(game->move == "b")
                {
                    QString sendMessage = "!;go;b;?";
                    TCPSocket->write(sendMessage.toStdString().c_str());
                }
            }
        }
    }
}

void MainWindow::send_data_to_server()
{
    QString tru;
    //if (game->)
    {
        if(game->exit)
        {
            TCPSocket->write("!;exit;?");
            game->exit == false;
        }
        if (game->ready)
        {
            QString sendMessage = "!;rdy;1;?";
            TCPSocket->write(sendMessage.toStdString().c_str());
        }
        if(game->ready)

        TCPSocket->write((game->ready == 1 ? "ready" : "not ready"));
        if (!game->ready)
        {
            QString sendMessage = "!;rdy;0;?";
            TCPSocket->write(sendMessage.toStdString().c_str());
        }
    }
}






