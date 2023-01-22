#include "mainwindow.h"
#include "game.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QGraphicsScene * scene  = new QGraphicsScene();

//    QGraphicsRectItem * rect = new QGraphicsRectItem();
//    rect->setRect(0,0, 100, 100);
//    scene->addItem(rect);

//    QGraphicsView * view = new QGraphicsView(scene);
//    view->show();

    return a.exec();
}
