#include "Frontend/Windows/mainMenu.h"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu menu;

    menu.show();

    return a.exec();
}
