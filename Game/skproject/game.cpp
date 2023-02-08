#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) : QFrame(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->rdy_1->setStyleSheet("background-color: orange");
    ui->readyColor->setStyleSheet("background-color: orange");
}
Game::~Game(){ delete ui; }

QString Game::getNickname()                 { return this->nickname; }

void Game::setNickname(QString nickname)    { this->nickname = nickname; }
void Game::setData(QString data)            { this->data = data; }
void Game::setDataList()                    { this->dataList = this->data.split(";"); }
void Game::setDataSize()                    { this->dataSize = this->dataList.size(); }

void Game::setDataSublists() //dataList: Bombs, Bricks, RangeBombs, Player Stats
{
    if(this->dataList[1] == "game")
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
        ui->console->setText(this->dataListBricks.join(",") + "\n" + this->dataListBombs.join(",")+
                             + "\n" + this->dataListRangeBombs.join(",") + "\n" + this->dataListStats.join(","));
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
    //inputData.sliced(0, inputData.size());
    this->updateDataFromServer(serverData);
    this->setNicksOnTheRight();
    this->setDataOnTheRight();
}

/*
 * Example: !;nicks;carl;bot;cos;ktos;1;0;1;1;?
 */
void Game::setNicksOnTheRight()
{
    if (this->dataList[1] == "nicks" && legal())
    {
        QStringList names = this->dataList;
        names.removeOne(this->nickname);
        // pieces[0] = pieces[0].last(pieces[0].size()-1);
        ui->Player1->setTitle(this->nickname);
        ui->Player2->setTitle(names[2]);
        ui->Player3->setTitle(names[3]);
        ui->Player4->setTitle(names[4]);
        ui->rdy_2->setStyleSheet(names[6] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_3->setStyleSheet(names[7] == "1" ? "background-color: green" : "background-color: orange");
        ui->rdy_4->setStyleSheet(names[8] == "1" ? "background-color: green" : "background-color: orange");
    }
}

/*
 * Update text when it comes from the server.
 * TODO
 *  - edit default strings to strings in parameter data
*/
void Game::setDataOnTheRight()
{
    if (this->dataList[1] == "game" && legal())
    {
//        int skipPosDataA = 0, skipPosDataB = 0, skipPosDataC = 0, skip = 2, skipMove = 3, playerDataSize = 8;
//        skipPosDataA = (this->dataList[skip]).toInt() * 2 + 1;              // 3; 1;1; 1;1; 1;1 = 7 pos
//        skipPosDataB = (this->dataList[skip+skipPosDataA].toInt() * 2 + 1); // 4; 1;1; 1;1; 1;1; 1;1; = 9 pos
//        skipPosDataC = (this->dataList[skip+skipPosDataA+skipPosDataB].toInt() * 3 + 1);
//        int i = skipPosDataA + skipPosDataB + skipPosDataC + skip + skipMove + 1;      // example: 2 + 7 + 9 + 3 = 21 pos
//        int players = this->dataList[skipPosDataA + skipPosDataB + skipPosDataC + skip].toInt();
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
        ui->rdy_1->setStyleSheet("background-color: green");
    }
    else
    {
        this->ready = false;

        ui->readyBtn->setText("Not ready");
        ui->readyColor->setStyleSheet("background-color: orange");
        ui->rdy_1->setStyleSheet("background-color: orange");
    }
}

void Game::on_exitBtn_clicked()
{
    this->exit = true;
    this->close();
}
