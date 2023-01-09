#include "Frontend/environment_stats.h"
#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <QGraphicsScene>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationView menu(new Environment());

    new Environment_Stats(menu);


    return a.exec();
}
