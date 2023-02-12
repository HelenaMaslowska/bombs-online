#ifndef GAME_H
#define GAME_H

#include <QFrame>
#include <QPainter>
#include <QPen>
#include <QCloseEvent>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QKeyEvent>
#include <QDir>
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
    void setMap(QString nr);
    void setData(QString data);
    void clearDataList();
    void setDataList();
    void setDataSublists();
    void setDataSize();
    void setNicksOnTheRight();
    void setDataOnTheRight();
    void setConsoleResult();

    void updateDataFromServer(QString serverData);
    void serverData(QString inputData);
    bool legal();
    void enableReadyBtn();
    void disableReadyBtn();
    void setGreens();
    QString* openMap();
    virtual void paintEvent(QPaintEvent *);
    //void closeEvent(QCloseEvent *event);

protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

public slots:
    void on_readyBtn_clicked();
    void on_exitBtn_clicked();

signals:
    void readyNo();
    void readyYes();
    void keyboardUp();
    void keyboardDown();
    void keyboardLeft();
    void keyboardRight();
    void keyboardBomb();
    void quitGameUI();

public:
    Ui::Game *ui;
    QString nickname;

public:
    bool ready = false;
    bool exit = false;
    //QString move = "";
    QString data;                   // string of input data
    QStringList dataList;           // splited 1 command
    QStringList dataListBricks;     // list of destroyable blocks
    QStringList dataListBombs;      // list of bombs
    QStringList dataListRangeBombs; // list of range bombs
    QStringList dataListStats;      // show them on the right
    QStringList dataListPowerups;    // every powerup shown in game
    QString mapNumber = "0";        // number of map, 0-3
    int players;                    // number of players, to show them on the screen 1-4
    int playerDataSize = 8;         // size of data that will be use further
    int dataSize = 0;
};

#endif // GAME_H
