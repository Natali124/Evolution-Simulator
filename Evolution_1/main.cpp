#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationView menu(new Environment());
    MainWindow w; //start screen window
    w.show();

    return a.exec();
}
