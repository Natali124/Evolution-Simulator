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
    MainMenu menu;

    menu.show();
    return a.exec();
}
