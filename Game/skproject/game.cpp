#include "game.h"
#include "ui_game.h"

QString googleMaps[4][15] = {
    {
        "111111111111111",
        "100221000122001",
        "101122202221101",
        "122012101210221",
        "120110101011021",
        "121002212200121",
        "121211010112121",
        "100210202012001",
        "121211010112121",
        "121002212200121",
        "120110101011021",
        "122012101210221",
        "101122202221101",
        "100221000122001",
        "111111111111111"
    },
    {
        "111111111111111",
        "100222212222001",
        "101111000111101",
        "121002212200121",
        "121021111120121",
        "101002020200101",
        "102210101012201",
        "110112020211011",
        "102210101012201",
        "101002020200101",
        "121021111120121",
        "121002212200121",
        "101111000111101",
        "100222212222001",
        "111111111111111"
    },
    {
        "111111111111111",
        "100202020202001",
        "101010111010101",
        "121202212200121",
        "101101111101101",
        "121200212002121",
        "101011000110101",
        "120202020202021",
        "101011000110101",
        "121200212002121",
        "101101111101101",
        "121002212200121",
        "101010111010101",
        "100202020202001",
        "111111111111111"
    },
    {
        "111111111111111",
        "100121202121001",
        "121000212000121",
        "122012111210221",
        "121100212001121",
        "100201202102001",
        "111011101110111",
        "122002202200221",
        "111011101110111",
        "100201202102001",
        "121100212001121",
        "122012111210221",
        "121000212000121",
        "100121202121001",
        "111111111111111"
    }
};
Game::Game(QWidget *parent) : QFrame(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->readyColor->setStyleSheet("background-color: orange");
}
Game::~Game(){ delete ui; }

QString Game::getNickname()                 { return this->nickname; }
void Game::setMap(QString nr)               { this->mapNumber = nr; }
void Game::setNickname(QString nickname)    { this->nickname = nickname; }
void Game::setData(QString data)            { this->data = data; }
void Game::clearDataList()                  { this->dataList.clear(); }

void Game::setDataList()
{
    QString message = this->data;
    QString temp_msg="";
    for(int j=0;j<message.length();j++)
    {
        if(message[j]=='!')
        {
            temp_msg="!";
            continue;
        }
        if(message[j]=='?')
        {
            temp_msg+="?";                  //!;rdy;0;?
            this->data.mid(temp_msg.length());
            this->dataList = temp_msg.split(";");
            qDebug(this->dataList.join(" ").toLatin1());
            break;
        }
        temp_msg+=message[j];
    }
}

void Game::setDataSize()                    { this->dataSize = this->dataList.size(); }

void Game::setDataSublists() //dataList: Bombs, Bricks, RangeBombs, Player Stats
{
    if(legal() && this->dataList[1] == "game")
    {
        int skipPosDataA, skipPosDataB, skipPosDataC, skip = 2;
        skipPosDataA = this->dataList[skip].toInt() * 2 + 1;                // 3; 1;1; 1;1; 1;1 = 2*3+1 = 7 pos
        skipPosDataB = this->dataList[skip+skipPosDataA].toInt() * 2 + 1;   // 4; 1;1; 1;1; 1;1; 1;1; = 2*4+1 = 9 pos
        skipPosDataC = this->dataList[skip+skipPosDataA+skipPosDataB].toInt() * 3 + 1;
        int i = skipPosDataA + skipPosDataB + skipPosDataC + skip;          // example: 2 + 7 + 9 + 3 = 21 pos
        int players = this->dataList[skipPosDataA + skipPosDataB + skipPosDataC + skip].toInt();

        this->players = players;
        this->dataListBricks = this->dataList.sliced(skip, skipPosDataA);
        this->dataListBombs = this->dataList.sliced(skipPosDataA+skip, skipPosDataB);
        this->dataListRangeBombs = this->dataList.sliced(skipPosDataA+skipPosDataB+skip, skipPosDataC);
        this->dataListStats = this->dataList.sliced(i + 1, this->playerDataSize*players); //1 is for skip the number of players
        //ui->console->setText(this->dataListBricks.join(",") + "\n" + this->dataListBombs.join(",")+
        //                     + "\n" + this->dataListRangeBombs.join(",") + "\n" + this->dataListStats.join(","));
    }
}
bool Game::legal()
{
    if (dataList[0][0] == '!' && dataList[this->dataSize - 1] == '?')
        return true;
    else
        return false;
}

/*
 * Set data bringing from server.
 */
void Game::updateDataFromServer(QString serverData)
{
    this->setData(serverData);
    this->setDataList();
    this->setDataSize();
    this->setDataSublists();
}

/*
 * Main function to serve data on the Game class.
 */
void Game::serverData(QString serverData)
{
    //this->ui->console->setText(serverData.split(";").join("a"));
    this->updateDataFromServer(serverData);     // NEED TO BE FIRST, SET DATA IN CLASS
    this->setNicksOnTheRight();
    this->setDataOnTheRight();
    this->update();
}

/*
 * Example: !;nicks;carl;bot;cos;ktos;1;0;1;1;?
 */
void Game::setNicksOnTheRight()
{
    if (legal() && this->dataList[1] == "nicks")
    {
        QStringList names = this->dataList;
        //int index = this->dataList.at(this->nickname);       // TODO update accessibility correctly, now is 3 next
        //names.removeOne(this->nickname);                      // for being first on list
        ui->Player1->setTitle(names[2]);
        ui->Player2->setTitle(names[3]);
        ui->Player3->setTitle(names[4]);
        ui->Player4->setTitle(names[5]);
        ui->rdy_1->setStyleSheet(names[6] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_2->setStyleSheet(names[7] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_3->setStyleSheet(names[8] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_4->setStyleSheet(names[9] == "1" ? "background-color: green" : "background-color: orange");
    }
}

/*
 * Update text when it comes from the server.
*/
void Game::setDataOnTheRight()
{
    if (legal() && this->dataList[1] == "game")
    {
        int i = 3;
        ui->HP_1->setText(this->dataListStats[i]);
        ui->Speed_1->setText(this->dataListStats[i+1]);
        ui->MaxBombs_1->setText(this->dataListStats[i+2]);
        ui->StrengthBombs_1->setText(this->dataListStats[i+3]);
        i += this->playerDataSize;

        ui->HP_2->setText(this->dataListStats[i]);
        ui->Speed_2->setText(this->dataListStats[i+1]);
        ui->MaxBombs_2->setText(this->dataListStats[i+2]);
        ui->StrengthBombs_2->setText(this->dataListStats[i+3]);
        i += this->playerDataSize;
        if (players >= 3)
        {
            ui->HP_3->setText(this->dataListStats[i]);
            ui->Speed_3->setText(this->dataListStats[i+1]);
            ui->MaxBombs_3->setText(this->dataListStats[i+2]);
            ui->StrengthBombs_3->setText(this->dataListStats[i+3]);
            i += this->playerDataSize;
        }
        else
        {
            ui->HP_3->setText("0");
            ui->Speed_3->setText("0");
            ui->MaxBombs_3->setText("0");
            ui->StrengthBombs_3->setText("0");
        }
        if (players >= 4)
        {
            ui->HP_4->setText(this->dataListStats[i]);
            ui->Speed_4->setText(this->dataListStats[i+1]);
            ui->MaxBombs_4->setText(this->dataListStats[i+2]);
            ui->StrengthBombs_4->setText(this->dataListStats[i+3]);
        }
        else
        {
            ui->HP_4->setText("0");
            ui->Speed_4->setText("0");
            ui->MaxBombs_4->setText("0");
            ui->StrengthBombs_4->setText("0");
        }
    }
}
void Game::enableReadyBtn()
{
    ui->readyBtn->setText("Not ready");
    ui->readyColor->setStyleSheet("background-color: orange");
    this->ui->readyBtn->setEnabled(true);
}

void Game::disableReadyBtn()
{
    ui->readyBtn->setText("Ready");
    ui->readyColor->setStyleSheet("background-color: green");
    this->ui->readyBtn->setEnabled(false);
}

void Game::setGreens()
{
    ui->readyColor->setStyleSheet("background-color: green");
}

//QString* Game::openMap()        // też działa ale ma ścieżkę absolutną
//{
//    QDir dir("../map" + this->mapNumber + ".txt"); //debug ma gdzie indziej więc nawet z QDir nie wyciągniesz ścieżki xd
//    ui->console->setText(dir.currentPath());

//    QFile file("/home/helena/Projekt/skproject/map" + this->mapNumber + ".txt");
//    if(!file.exists())                  { qCritical() << "File not found";   }
//    if(!file.open(QIODevice::ReadOnly)) { qCritical() << file.errorString(); }
//    QTextStream stream(&file);
//    // qInfo() << file.readAll();
//    QString* arr = new QString[15];
//    int i = 0;
//    while (!stream.atEnd())
//    {
//        QString line = stream.readLine();
//        arr[i] = line;
//        ++i;
//    }
//    file.close();
//    return arr;
//}

QString* Game::openMap()
{
    return googleMaps[this->mapNumber.toInt()];
}

void Game::paintEvent(QPaintEvent *event)
{
    int margin = ui->frame->x();
    int block_size = 32;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
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
//            if(map[i].toStdString()[j] == '2')
//            {
//                painter.setBrush(Qt::DiagCrossPattern);
//                painter.drawRect(QRect(i*block_size+margin, j*block_size+margin, block_size, block_size));
//            }
//            if(map[i].toStdString()[j] == '3')      // bombs damage, change to 2 to see them
//            {
//                painter.setBrush(Qt::SolidPattern);
//                painter.drawEllipse(QPointF(i*(block_size)+margin+block_size/2,j*block_size+margin+block_size/2), block_size/4, block_size/4);
//            }
        }
    }
    for(int i=1 ; i+1< this->dataListBricks.size(); i+=2)
    {
        int x = this->dataListBricks[i].toInt();
        int y = this->dataListBricks[i+1].toInt();
        painter.setBrush(Qt::DiagCrossPattern);
        painter.drawRect(QRect(y*block_size+margin, x*block_size+margin, block_size, block_size));
    }
    for(int i=1 ; i+1< this->dataListBombs.size(); i+=2)
    {
        int x = this->dataListBombs[i].toInt();
        int y = this->dataListBombs[i+1].toInt();
        painter.setBrush(Qt::SolidPattern);
        painter.drawEllipse(QPointF(y*block_size+margin+block_size/2,x*block_size+margin+block_size/2), block_size/4, block_size/4);
    }
    for(int i=0 ; i+7 < this->dataListStats.size(); i+=8)   // TODO poprawić na większą precyzję bo narazie przyjmuje tylko zaokrąglone do setek
    {
        float x = this->dataListStats[i].toFloat()/100;
        float y = this->dataListStats[i+1].toFloat()/100;
        qDebug() << x << y;
        //ui->console->setText((this->dataListStats[i+1].toFloat()/100));
        painter.setBrush(Qt::SolidPattern);
        pen.setColor(Qt::red);
        painter.setPen(pen);

        painter.drawEllipse(QPointF(y*block_size+margin+block_size/2,x*block_size+margin+block_size/2), block_size*2/5, block_size*2/5);
    }
    pen.setColor(Qt::black);

}

//void Game::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app {
//    event->ignore();
//    if (QMessageBox::Yes == QMessageBox::question(this, "Exit?", "You will lose if you exit!", QMessageBox::Yes | QMessageBox::No))
//    { this->exit = true; event->accept(); }
//    else { this->exit = false; } }


void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        //this->move = "u";
        emit keyboardUp();
    }
    if(event->key() == Qt::Key_S)
    {
        //this->move = "d";
        emit keyboardDown();
    }
    if(event->key() == Qt::Key_A)
    {
        //this->move = "l";
        emit keyboardLeft();
    }
    if(event->key() == Qt::Key_D)
    {
        //this->move = "r";
        emit keyboardRight();
    }
    if(event->key() == Qt::Key_X)
    {
        //this->move = "b";
        emit keyboardBomb();
    }
}

void Game::on_readyBtn_clicked()
{
    if (ui->readyBtn->text() == "Not ready")
    {
        this->ready = true;
        ui->readyBtn->setText("Ready");
        ui->readyColor->setStyleSheet("background-color: green");
        emit readyYes();
    }
    else
    {
        this->ready = false;
        ui->readyBtn->setText("Not ready");
        ui->readyColor->setStyleSheet("background-color: orange");
        emit readyNo();
    }
}

void Game::on_exitBtn_clicked()
{
    this->exit = true;
    this->close();
    emit quitGameUI();
}
