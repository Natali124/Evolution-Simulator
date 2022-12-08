#include "environment.h"
#include "mainmenu.h"
#include <QApplication>
#include <iostream>
#include <QtGui>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    srand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MainMenu menu;
    menu.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &menu.display._scene, SLOT(advance()));
    timer.start(1000 / 33);

    return a.exec();
}
