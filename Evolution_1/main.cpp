#include "environment.h"
#include "mainmenu.h"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>
#include <QTimer>
#include <QTime>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *statswindow = new QWidget;
    statswindow->setWindowTitle("Statistics of the simulation");
    //
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MainMenu menu;
    menu.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &menu.display._scene, SLOT(advance()));
    timer.start(1000 / 33);

    return a.exec();
}
