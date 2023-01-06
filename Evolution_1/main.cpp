//#include "Frontend/Windows/mainMenu.h"
#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainMenu menu;
    MainWindow w;
    w.show();
    //menu.show();


    return a.exec();
}
