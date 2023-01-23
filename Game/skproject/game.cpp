#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent, QString nickname) : QFrame(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->Player1->setTitle("");

}

Game::~Game()
{
    delete ui;
}
QString Game::getNickname()
{
    return this->nickname;
}
void Game::setNickname(QString nickname)
{
    ui->Player1->setTitle(nickname);
}

/*
 * Main function to serve data on the Game class.
 */
void Game::serverInputDealer(QString inputData)
{
    QString playersData = inputData.sliced(0, inputData.size()); //TODO piece of data
    setDataOnTheRight(playersData);

}

/*
 * Update text when it comes from the server.
 * TODO
 *  - edit default strings to strings in parameter data
*/
void Game::setDataOnTheRight(QString data)
{
    ui->HP_1->setText("3");
    ui->Speed_1->setText("0.05");
    ui->MaxBombs_1->setText("1");
    ui->StrengthBombs_1->setText("1");

    ui->HP_2->setText("3");
    ui->Speed_2->setText("0.05");
    ui->MaxBombs_2->setText("1");
    ui->StrengthBombs_2->setText("1");

    ui->HP_3->setText("3");
    ui->Speed_3->setText("0.05");
    ui->MaxBombs_2->setText("1");
    ui->StrengthBombs_2->setText("1");

    ui->HP_4->setText("3");
    ui->Speed_4->setText("0.05");
    ui->MaxBombs_2->setText("1");
    ui->StrengthBombs_2->setText("1");

}

QString* open_map()
{
    QFile file = QFile("/home/helena/Projekt/skproject/map1.txt");
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
    auto map = open_map();
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

void Game::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Exit?", "You will lose if you exit!", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }
}
