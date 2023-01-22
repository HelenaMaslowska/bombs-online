#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent, QString nickname) : QFrame(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    ui->Player1->setTitle(nickname);
}

Game::~Game()
{
    delete ui;
}


void Game::paintEvent(QPaintEvent *event)
{
    int margin = 20;
    int block_size = 32;
    QPainter painter(this);
    for (int i=0;i < 12; i++)
    {
        for (int j=0;j < 12; j++)
        {
            painter.drawRect(QRect(i*block_size+margin, j*block_size+margin, block_size, block_size));
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
