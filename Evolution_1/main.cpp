#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include <QApplication>
#include <iostream>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationView menu(new Environment());

    return a.exec();
}
