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
        "101000212000101",
        "122012111210221",
        "121100212001121",
        "100201202102001",
        "111011101110111",
        "122002202200221",
        "111011101110111",
        "100201202102001",
        "121100212001121",
        "122012111210221",
        "101000212000101",
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

/*
 * Main function to serve data on the Game class.
 */
void Game::serverData(QString serverData)
{
    this->updateDataFromServer(serverData);     // NEED TO BE FIRST, SET DATA IN CLASS
    this->update();
}

/*
 * Set all input data bringing from server. Partial data does not be modified.
 */
void Game::updateDataFromServer(QString serverData)
{
    this->setData(serverData);
    while(this->data.length() > 4 && this->data[this->data.length()-1] == '?')
    {
        this->setDataList();
        this->setDataSize();
        if (this->dataList[1] == "game")    this->setDataSublists();
        if (this->dataList[1] == "game")    this->setDataOnTheRight();
        if (this->dataList[1] == "nicks")   this->setNicksOnTheRight();
        this->setConsoleResult();
    }
}

QString Game::getNickname()                 { return this->nickname; }
void Game::setMap(QString nr)               { this->mapNumber = nr; }
void Game::setNickname(QString nickname)    { this->nickname = nickname; }
void Game::setData(QString data)            { this->data.append(data); }
void Game::clearDataList()                  { this->dataList.clear(); }
void Game::setDataSize()                    { this->dataSize = this->dataList.size(); }
void Game::setDataList()
{
    //qDebug(this->data.toLatin1());
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
            this->data = this->data.mid(temp_msg.length());
            this->dataList = temp_msg.split(";");
            break;
        }
        temp_msg+=message[j];
    }
}

void Game::setDataSublists() //dataList: Bricks, Bombs, RangeBombs, Powerups, s Stats
{
    int bricks, bombs, rangebombs, listStats, powerups, skip = 2;    //2 = game + !
    bricks = this->dataList[skip].toInt() * 2 + 1;                      // 3; 1;1; 1;1; 1;1 = 2*3+1 = 7  sum of these elements
    bombs = this->dataList[skip+bricks].toInt() * 2 + 1;                // 4; 1;1; 1;1; 1;1; 1;1; = 2*4+1 = 9  sum of these elements
    rangebombs = this->dataList[skip+bricks+bombs].toInt() * 3 + 1;     // 1; 4;5;2; = 4 sum of these elements
    powerups = this->dataList[skip+bricks+bombs+rangebombs].toInt() * 3 + 1;

    this->dataListBricks = this->dataList.sliced(skip, bricks);
    this->dataListBombs = this->dataList.sliced(bricks+skip, bombs);
    this->dataListRangeBombs = this->dataList.sliced(bricks+bombs+skip, rangebombs);
    this->dataListPowerups = this->dataList.sliced(bricks+bombs+rangebombs+skip, powerups);

    listStats = skip + bricks + bombs + rangebombs + powerups + 1;              // example: 2 + 7 + 9 + 4 = 22 pos
    int  players = this->dataList[skip+bricks+bombs+rangebombs+powerups].toInt();
    this->players = players;
    this->dataListStats = this->dataList.sliced(listStats, this->playerDataSize*players); //1 is for skip the number of players

    //ui->console->setText(this->dataListBricks.join(",") + "\n" + this->dataListBombs.join(","));
}
bool Game::legal()
{
    if (dataList[0][0] == '!' && dataList[this->dataSize - 1] == '?')
        return true;
    else
        return false;
}

/*
 * Example: !;nicks;carl;bot;cos;ktos;1;0;1;1;?
 */
void Game::setNicksOnTheRight()
{
    QStringList names = this->dataList;
    ui->Player1->setTitle(names[2]);
    ui->Player2->setTitle(names[3]);
    ui->Player3->setTitle(names[4]);
    ui->Player4->setTitle(names[5]);
    ui->rdy_1->setStyleSheet(names[6] == "1" ? "background-color: green" : "background-color: orange");
    ui->rdy_2->setStyleSheet(names[7] == "1" ? "background-color: green" : "background-color: orange");
    ui->rdy_3->setStyleSheet(names[8] == "1" ? "background-color: green" : "background-color: orange");
    ui->rdy_4->setStyleSheet(names[9] == "1" ? "background-color: green" : "background-color: orange");
}

/*
 * Update text when it comes from the server.
*/
void Game::setDataOnTheRight()
{
    int i = 3;
    if (players >= 1)
    {
        ui->HP_1->setText(this->dataListStats[i]);
        ui->Speed_1->setText(this->dataListStats[i+1]);
        ui->MaxBombs_1->setText(this->dataListStats[i+2]);
        ui->StrengthBombs_1->setText(this->dataListStats[i+3]);
        i += this->playerDataSize;
    }

    if (players >= 2)
    {
        ui->HP_2->setText(this->dataListStats[i]);
        ui->Speed_2->setText(this->dataListStats[i+1]);
        ui->MaxBombs_2->setText(this->dataListStats[i+2]);
        ui->StrengthBombs_2->setText(this->dataListStats[i+3]);
        i += this->playerDataSize;
    }
    else
    {
        ui->HP_2->setText("0");
        ui->Speed_2->setText("0");
        ui->MaxBombs_2->setText("0");
        ui->StrengthBombs_2->setText("0");
    }
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
    if (players == 4)
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

void Game::setConsoleResult()
{
    if (legal() && this->dataList[1] == "win")
    {
        ui->console->setText("Congratulations! You win!");
    }
    if (legal() && this->dataList[1] == "lose")
    {
        ui->console->setText("You lost :c   \nNow you get spectate mode O.o");
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
    ui->rdy_1->setStyleSheet("background-color: green");
    ui->rdy_2->setStyleSheet("background-color: green");
    ui->rdy_3->setStyleSheet("background-color: green");
    ui->rdy_4->setStyleSheet("background-color: green");
}

void Game::setInformations()
{
    ui->console->setText("green -=- range \ngray -=- max bombs \nblue -=- speed \nred -=- HP \n yellow -=- immortality");
}


QString* Game::openMap()
{
    if (legal() && this->dataList[1] == "map")
    {
        this->mapNumber = this->dataList[2];
    }
    return googleMaps[this->mapNumber.toInt()];
}

void Game::paintEvent(QPaintEvent *)
{
    int margin = ui->frame->x();
    int block_size = 32;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    auto map = openMap();
    for (int i=0;i < 15; i++)
    {
        for (int j=0;j < 15; j++)
        {
            if(map[i].toStdString()[j] == '1')
            {
                painter.setBrush(Qt::SolidPattern);
                painter.drawRect(QRect(j*block_size+margin, i*block_size+margin, block_size, block_size));
            }
        }
    }
    for(int i=1 ; i+1 < this->dataListBricks.size(); i+=2)
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
    for(int i=0 ; i+7 < this->dataListStats.size(); i+=8)
    {
        float x = this->dataListStats[i].toFloat()/100;
        float y = this->dataListStats[i+1].toFloat()/100;
        painter.setBrush(Qt::SolidPattern);
        if(this->dataListStats[i+7].toInt() == 1) pen.setColor(Qt::yellow);
        else pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.drawEllipse(QPointF(y*block_size+margin+block_size/2,x*block_size+margin+block_size/2), block_size*2/5, block_size*2/5);
    }
    pen.setColor(Qt::black);
    for(int i=1 ; i+1< this->dataListPowerups.size(); i+=3)
    {
        int x = this->dataListPowerups[i].toInt();
        int y = this->dataListPowerups[i+1].toInt();
        int color = this->dataListPowerups[i+2].toInt();
        if (color == 1) pen.setColor(Qt::green);        // range
        if (color == 2) pen.setColor(Qt::gray);         // max bombs
        if (color == 3) pen.setColor(Qt::blue);         // movement speed
        if (color == 4) pen.setColor(Qt::red);          // hp
        if (color == 5) pen.setColor(Qt::yellow);       // immortality
        painter.setBrush(Qt::DiagCrossPattern);
        painter.setPen(pen);
        painter.drawRect(QRect(y*block_size+margin+block_size/4, x*block_size+margin+block_size/4, block_size/2, block_size/2));
    }
    pen.setColor(Qt::black);
    for(int i=1 ; i+1< this->dataListRangeBombs.size(); i+=3)
    {
        int x = this->dataListRangeBombs[i].toInt();
        int y = this->dataListRangeBombs[i+1].toInt();
        int range = this->dataListRangeBombs[i+2].toInt();
        painter.setBrush(Qt::SolidPattern);
        pen.setColor(Qt::yellow);
        painter.setPen(pen);
        painter.drawEllipse(QPointF(y*block_size  +margin+block_size/2, x*block_size  +margin+block_size/2), block_size/3, block_size/3);
        for (int far = -range; far<=range; far++)
        {
            painter.drawEllipse(QPointF((y+far)*block_size  +margin+block_size/2, x*block_size  +margin+block_size/2),
                                                    block_size/3, block_size/3);
            painter.drawEllipse(QPointF(y*block_size  +margin+block_size/2, (x+far)*block_size  +margin+block_size/2),
                                                    block_size/3, block_size/3);
        }
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
    if(event->key() == Qt::Key_W) { emit keyboardUp();      }
    if(event->key() == Qt::Key_S) { emit keyboardDown();    }
    if(event->key() == Qt::Key_A) { emit keyboardLeft();    }
    if(event->key() == Qt::Key_D) { emit keyboardRight();   }
    if(event->key() == Qt::Key_X) { emit keyboardBomb();    }
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
