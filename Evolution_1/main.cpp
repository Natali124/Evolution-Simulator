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

    //for stats:
    MainWindow window(menu);
    window.resize(800, 600);
    window.show();

    return a.exec();
}
