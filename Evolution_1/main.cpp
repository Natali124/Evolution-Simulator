#include "environment.h"
#include "Frontend/Windows/mainmenu.h"
#include <QApplication>
#include <iostream>
#include <QtGui>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu menu(new Environment());

    return a.exec();
}
