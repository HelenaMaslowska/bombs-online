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
    void setDataList();
    void setDataSublists();
    void setDataSize();
    void setNicksOnTheRight();
    void setDataOnTheRight();

    void updateDataFromServer(QString serverData);
    void serverData(QString inputData);
    bool legal();
    void enableReadyBtn();
    void disableReadyBtn();
    void setGreens();
    QString* openMap();
    virtual void paintEvent(QPaintEvent *event);
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
    bool ready = 0;
    bool exit = 0;
    //QString move = "";
    QString data;
    QStringList dataList;
    QStringList dataListBricks;
    QStringList dataListBombs;
    QStringList dataListRangeBombs;
    QStringList dataListStats;
    QString mapNumber = "1";
    int players;
    int playerDataSize = 8;
    int dataSize = 0;
};

#endif // GAME_H
