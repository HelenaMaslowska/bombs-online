#ifndef GAME_H
#define GAME_H

#include <QFrame>
#include <QPainter>
#include <QPen>
#include <QCloseEvent>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <iostream>
#include <fstream>

namespace Ui
{
    class Game;
}

class Game : public QFrame
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr, QString nickname = "");
    ~Game();
    QString getNickname();
    void setNickname(QString nickname);

    void serverInputDealer(QString inputData);
    void setDataOnTheRight(QString data);
    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::Game *ui;
    QString nickname;
};

#endif // GAME_H
