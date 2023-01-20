#include "Frontend/startscreen.h"
#include "Neural_Network/reading.hpp"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new startscreen;

    return a.exec();
}
