#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include "Neural_Network/reading.hpp"
#include "Neural_NetworK/nn_evolution.hpp"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>
#include <stdio.h>
#include <conio.h>
#include <Python.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationView menu(new Environment());
    MainWindow w; //start screen window
    w.show();

    Py.Initialize();
    PyRun_SimpleString("print('hello from python')");
    Py.Finilize();


    return a.exec();
}
