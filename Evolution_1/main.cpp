#include "Frontend/startscreen.h"
#include "Frontend/startscreen/propertyslider.h"
#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include "Neural_Network/reading.hpp"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new startscreen;
    new PropertySlider;
    SimulationView menu(new Environment());
//    MainWindow w; //start screen window
//    w.show();

    return a.exec();
}
