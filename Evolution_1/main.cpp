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
    SimulationView menu(new Environment());
    MainWindow w; //start screen window

//    auto creature = new Creature;

//    auto w = new QMainWindow;
//    auto layout = new QVBoxLayout;
//    auto slider = new PropertySlider("Size:", creature, &Creature::set_size, 0, w);
//    layout->addWidget(slider);
//    auto central = new QWidget(w); central->show();
//    w->setCentralWidget(central);
//    central->setLayout(layout);
//    w->show();

    return a.exec();
}
