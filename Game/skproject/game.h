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
#include <string>
#include <bits/stdc++.h>

namespace Ui
{
    class Game;
}

class Game : public QFrame
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    QString getNickname();
    void setNickname(QString nickname);
    void setMap(int nr);
    void setData(QString data);
    void setDataList();
    void setDataSublists();
    void setDataSize();
    void setNicksOnTheRight();
    void setDataOnTheRight();

    void updateDataFromServer(QString serverData);
    void serverData(QString inputData);
    bool legal();

    virtual void paintEvent(QPaintEvent *event);
    void paintMap();
    void repaintMap();
    //void closeEvent(QCloseEvent *event);

public slots:
    void on_readyBtn_clicked();
    void on_exitBtn_clicked();

private:
    Ui::Game *ui;
    QString nickname;

public:
    bool ready = 0;
    bool exit = 0;
    bool move = "d";
    QString data;
    QStringList dataList;
    QStringList dataListBricks;
    QStringList dataListBombs;
    QStringList dataListRangeBombs;
    QStringList dataListStats;
    int mapNumber = 1;
    int players;
    int playerDataSize = 8;
    int dataSize = 0;
};

#endif // GAME_H
