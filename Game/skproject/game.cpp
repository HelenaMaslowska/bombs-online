#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) : QFrame(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
}
Game::~Game(){ delete ui; }

QString Game::getNickname()                 { return this->nickname; }

void Game::setNickname(QString nickname)    { ui->Player1->setTitle(nickname); }
void Game::setData(QString data)            { this->data = data; }
void Game::setDataList()                    { this->dataList = this->data.split(";"); }
void Game::setDataSize()                    { this->dataSize = this->dataList.size(); }

bool Game::legal()
{
    if (dataList[0][0] == '!' && dataList[this->dataSize - 1] == '?')
        return true;
    else
        return false;
}

//void returnPosForData(QString data)
//{
//    if (legal() && )
//}

/*
 * Main function to serve data on the Game class.
 */
void Game::serverData(QString inputData)
{
    this->setData(inputData);
    this->setDataList();
    this->setDataSize();
    //QString playersData = inputData.sliced(0, inputData.size()); //TODO piece of data

    this->setDataOnTheRight();
    this->setNicksOnTheRight();
}

/*
 * Example: !;carl;bot;cos;ktos;1;0;1;1;?
 */
void Game::setNicksOnTheRight()
{
    QStringList pieces = data.split(";");
    int datasize = pieces.size();
    if (this->dataSize == 10 && legal())
    {
        // pieces[0] = pieces[0].last(pieces[0].size()-1);
        ui->Player1->setTitle(pieces[1]);
        ui->Player2->setTitle(pieces[2]);
        ui->Player3->setTitle(pieces[3]);
        ui->Player4->setTitle(pieces[4]);
        ui->rdy_1->setStyleSheet(pieces[5] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_2->setStyleSheet(pieces[6] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_3->setStyleSheet(pieces[7] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_4->setStyleSheet(pieces[8] == "1" ? "background-color: green" : "background-color: orange");
    }
}

/*
 * Update text when it comes from the server.
 * TODO
 *  - edit default strings to strings in parameter data
*/
void Game::setDataOnTheRight()
{
    if (legal())
    {
        ui->HP_1->setText("5");
        ui->Speed_1->setText("0.05");
        ui->MaxBombs_1->setText("1");
        ui->StrengthBombs_1->setText("1");

        ui->HP_2->setText("3");
        ui->Speed_2->setText("0.05");
        ui->MaxBombs_2->setText("1");
        ui->StrengthBombs_2->setText("1");

        ui->HP_3->setText("3");
        ui->Speed_3->setText("0.05");
        ui->MaxBombs_3->setText("1");
        ui->StrengthBombs_3->setText("1");

        ui->HP_4->setText("3");
        ui->Speed_4->setText("0.05");
        ui->MaxBombs_4->setText("1");
        ui->StrengthBombs_4->setText("1");
    }
}


QString* openMap()
{
    QFile file = QFile("/home/helena/Projekt/skproject/map3.txt");
    if(!file.exists())                  { qCritical() << "File not found";   }
    if(!file.open(QIODevice::ReadOnly)) { qCritical() << file.errorString(); }
    QTextStream stream(&file);
    // qInfo() << file.readAll();
    QString* arr = new QString[15];
    int i = 0;
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        arr[i] = line;
        ++i;
    }
    file.close();
    return arr;
}

void Game::paintEvent(QPaintEvent *event)
{
    int margin = 20;
    int block_size = 32;
    QPainter painter(this);
    QPen pen;
    painter.setPen(pen);
    auto map = openMap();
//    for(int i =0; i< 15; i++) { std::cout << map[i].toStdString() << std::endl; }
    for (int i=0;i < 15; i++)
    {
        for (int j=0;j < 15; j++)
        {
            if(map[i].toStdString()[j] == '1')
            {
                painter.setBrush(Qt::SolidPattern);
                pen.setColor(Qt::black);
                painter.drawRect(QRect(i*block_size+margin, j*block_size+margin, block_size, block_size));
            }
            if(map[i].toStdString()[j] == '2')
            {
                painter.setBrush(Qt::DiagCrossPattern);
                painter.drawRect(QRect(i*block_size+margin, j*block_size+margin, block_size, block_size));
            }
            if(map[i].toStdString()[j] == '3')      // bombs damage, change to 2 to see them
            {
                painter.setBrush(Qt::SolidPattern);
                painter.drawEllipse(QPointF(i*(block_size)+margin+block_size/2,j*block_size+margin+block_size/2), block_size/4, block_size/4);
            }
        }
    }
}

//void Game::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
//{
//    event->ignore();
//    if (QMessageBox::Yes == QMessageBox::question(this, "Exit?", "You will lose if you exit!", QMessageBox::Yes | QMessageBox::No))
//    {
//        this->exit = true;
//        event->accept();
//    }
//    else
//    {
//        this->exit = false;
//    }

//}

void Game::on_readyBtn_clicked()
{
    if (ui->readyBtn->text() == "Not ready")
    {
        this->ready = true;
        ui->readyBtn->setText("Ready");
        ui->readyColor->setStyleSheet("background-color: green");
    }
    else
    {
        this->ready = false;
        ui->readyBtn->setText("Not ready");
        ui->readyColor->setStyleSheet("background-color: orange");
    }
}

void Game::on_exitBtn_clicked()
{
    this->exit = true;
    this->close();
}

