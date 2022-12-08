#include "environment.h"
#include "mainmenu.h"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>
#include <QtGui>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 1000, 1000);
    QGraphicsView view(&scene);

    LivingBeing* being1 = new LivingBeing;
    being1->setPos(0, 0);
    scene.addItem(being1);

    LivingBeing* being2 = new LivingBeing;
    being2->setPos(100, 100);
    scene.addItem(being2);

    LivingBeing* being3 = new LivingBeing;
    being3->setPos(100, -100);
    scene.addItem(being3);

    //view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/backgrounds/images/forest.jpg"));

    //view.setCacheMode(QGraphicsView::CacheBackground);
    //view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Evolution"));
    view.resize(1000, 1000);
    view.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    timer.start(1000 / 33);

    return a.exec();
}
