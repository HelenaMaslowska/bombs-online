#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
    connect(game, SIGNAL(readyYes()),       this, SLOT(rdyYes()));
    connect(game, SIGNAL(readyNo()),        this, SLOT(rdyNo()));
    connect(game, SIGNAL(keyboardUp()),     this, SLOT(up()));
    connect(game, SIGNAL(keyboardDown()),   this, SLOT(down()));
    connect(game, SIGNAL(keyboardLeft()),   this, SLOT(left()));
    connect(game, SIGNAL(keyboardRight()),  this, SLOT(right()));
    connect(game, SIGNAL(keyboardBomb()),   this, SLOT(bomb()));
    connect(game, SIGNAL(quitGameUI()),     this, SLOT(backToStart()));
//    if (TCPSocket->isOpen()) { QMessageBox::information(this, "Hej! Miłego kodowania!", "Połączyłaś się ez"); }
}
MainWindow::~MainWindow()
{
    if(TCPSocket) TCPSocket->close();
    delete ui;
}

void MainWindow::enableStartBtn()
{
    ui->startBtn->setEnabled(true);
}

void MainWindow::connectToServer()
{
    TCPSocket = new QTcpSocket();
    TCPSocket->connectToHost(QHostAddress(this->address), this->port);
    connect(TCPSocket,SIGNAL(readyRead()),  this, SLOT(read_data_from_server()));
    TCPSocket->open(QIODevice::ReadWrite);
    enableStartBtn();
}

void MainWindow::on_confirmBtn_clicked()
{
    this->address = ui->addressInput->text();
    this->port = ui->portInput->text().toInt();
    connectToServer();
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
    this->ui->nickInput->setText("Nickname");
    TCPSocket->write("!;exit;?");
    this->show();
    //this->status = 1;
}
/*
 * When you click startBtn then MainWindow send nickname to the server.
 * Example: nick;Nick name;       -  "nick": prefix, "Nick name": player's input, ";": separator
 * Show new window and hide start menu. Set nickname in game.
 */
void MainWindow::on_startBtn_clicked() // send nickname to the server
{
    if (TCPSocket && TCPSocket->isOpen())
    {
        if(ui->nickInput->text() == "")
        {
            QMessageBox::information(this, "So you are noname?", "Type your special nickname!");
        }
        else
        {
            game->setInformations();
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
    }else { QMessageBox::information(this, "Hej! Miłego debugowania!", TCPSocket->errorString()); }
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
            QString MessageString = QString::fromStdString(data_from_server.toStdString());
            //ui->nickInput->setText(MessageString);
            game->serverData(MessageString);

            if(this->status == 3 && game->exit)
            {
                this->status = 1;
                game->mapNumber = "0";
                game->exit = false;

            }

            if(MessageString == "!;allrdy;?")
            {
                this->status = 3;
            }
            MessageString = "";
        }
    }
}



