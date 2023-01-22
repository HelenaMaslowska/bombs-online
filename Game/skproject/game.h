#ifndef GAME_H
#define GAME_H

#include <QFrame>
#include <QPainter>
#include <QCloseEvent>
#include <QMessageBox>
#include <QString>
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

    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::Game *ui;
};

#endif // GAME_H
