#include "Frontend/startscreen.h"
#include "Frontend/startscreen/propertyslider.h"
#include "Living_Beings/creature.h"
#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include "Neural_Network/reading.hpp"
#include "qboxlayout.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    SimulationView menu(new Environment());
    new startscreen;
    //MainWindow w; //start screen window
    //w.show();

    return a.exec();
}
