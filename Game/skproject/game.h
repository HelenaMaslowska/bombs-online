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

    void updateDataFromServer(QString serverData);
    void serverData(QString inputData);
    void setData(QString data);
    void setDataList();
    void setDataSublists();
    void setDataSize();
    bool legal();
    void setNicksOnTheRight();
    void setDataOnTheRight();
    virtual void paintEvent(QPaintEvent *event);
    //void closeEvent(QCloseEvent *event);

private slots:
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
    int players;
    int playerDataSize = 8;
    int dataSize = 0;
};

#endif // GAME_H
