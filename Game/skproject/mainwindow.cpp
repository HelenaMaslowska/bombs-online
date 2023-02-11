#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
    TCPSocket = new QTcpSocket();
    TCPSocket->connectToHost(QHostAddress::LocalHost, 8080);
    connect(TCPSocket,SIGNAL(readyRead()),  this, SLOT(read_data_from_server()));
    connect(game, SIGNAL(readyYes()),       this, SLOT(rdyYes()));
    connect(game, SIGNAL(readyNo()),        this, SLOT(rdyNo()));
    connect(game, SIGNAL(keyboardUp()),     this, SLOT(up()));
    connect(game, SIGNAL(keyboardDown()),   this, SLOT(down()));
    connect(game, SIGNAL(keyboardLeft()),   this, SLOT(left()));
    connect(game, SIGNAL(keyboardRight()),  this, SLOT(right()));
    connect(game, SIGNAL(keyboardBomb()),   this, SLOT(bomb()));
    connect(game, SIGNAL(quitGameUI()),     this, SLOT(backToStart()));
    TCPSocket->open(QIODevice::ReadWrite);
//    if (TCPSocket->isOpen()) { QMessageBox::information(this, "Hej! Miłego kodowania!", "Połączyłaś się ez"); }
}
MainWindow::~MainWindow() {
    if(TCPSocket) TCPSocket->close();
    delete ui;
}
void MainWindow::rdyYes()   { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;rdy;1;?"); }
void MainWindow::rdyNo()    { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;rdy;0;?"); }
void MainWindow::up()       { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;go;u;?"); }
void MainWindow::down()     { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;go;d;?"); }
void MainWindow::left()     { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;go;l;?"); }
void MainWindow::right()    { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;go;r;?"); }
void MainWindow::bomb()     { if (TCPSocket && TCPSocket->isOpen()) TCPSocket->write("!;go;b;?"); }

void MainWindow::backToStart()
{
    this->ui->nickInput->setText("");
    this->show();
    this->status = 1;
}
/*
 * When you click startBtn then MainWindow send nickname to the server.
 * Example: nick;Nick name;       -  "nick": prefix, "Nick name": player's input, ";": separator
 * Show new window and hide start menu. Set nickname in game.
 */
void MainWindow::on_startBtn_clicked() // send nickname to the server
{
    if(ui->nickInput->text() == "")
    {
        QMessageBox::information(this, "So you are noname?", "Type your special nickname!");
    }
    else
    {
        if (TCPSocket && TCPSocket->isOpen())
        {
            QString prefix = "!;nick;";
            QString nick = ui->nickInput->text();
            if(nick.size() > 15) nick = nick.sliced(0,15);
            QString sendMessage = prefix + nick + ";?";
            TCPSocket->write(sendMessage.toStdString().c_str());
            game->setNickname(nick);
            game->enableReadyBtn();
            game->show();
            this->hide();
            this->status = 2;
        }
        else { QMessageBox::information(this, "Hej! Miłego debugowania!", TCPSocket->errorString()); }
    }
}

/*
 * Exit using exitBtn.
 */
void MainWindow::on_exitBtn_clicked()
{
    this->close();
}

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
            if (MessageString.split(";")[1] == "map")
            {
                game->mapNumber = MessageString.split(";")[2];
            }
            game->serverData(MessageString);
            //game->setNicksOnTheRight(MessageString);


            if(game->exit)
            {
                TCPSocket->write("!;exit;?");
                game->exit == false;
            }

            if (this->status == 2)
            {
                if(MessageString == "!;allrdy;?")
                {
                    this->status = 3;
                    TCPSocket->write("!;go;s;?");
                    game->disableReadyBtn();
                    game->setGreens();
                }
            }
            MessageString = "";
        }
    }
}

//void MainWindow::send_data_to_server()
//{
//    QString tru;
//    //if (game->)
//    {
//        if(game->exit)
//        {
//            TCPSocket->write("!;exit;?");
//            game->exit == false;
//        }
//        if (game->ready)
//        {
//            QString sendMessage = "!;rdy;1;?";
//            TCPSocket->write(sendMessage.toStdString().c_str());
//        }
//        if(game->ready)

//        TCPSocket->write((game->ready == 1 ? "ready" : "not ready"));
//        if (!game->ready)
//        {
//            QString sendMessage = "!;rdy;0;?";
//            TCPSocket->write(sendMessage.toStdString().c_str());
//        }
//    }
//}






