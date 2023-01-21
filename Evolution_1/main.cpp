#include "Frontend/startscreen.h"
#include "Neural_Network/reading.hpp"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
//    SimulationView menu(new Environment());
    new startscreen;
    //MainWindow w; //start screen window
    //w.show();

    return a.exec();
}
