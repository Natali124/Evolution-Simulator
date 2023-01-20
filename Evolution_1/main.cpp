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
    SimulationView* menu_ptr = &menu;

    //choose only one graph to display, otherwise it is too heavy and crashes!

    //new Energy_perc(menu_ptr);  //predators and preys are treated as independent groups. Plots the percentage of preys/predators
    //having less/more than or equal to  half of their max energy (of preys among preys, of predators among predators)

    //new Average_size(menu_ptr); //Plots the average size of plants, preys and predators

    new Alive_perc(menu_ptr);  //plots the percentage of alive preys/predators/plants among all LBs.
    return a.exec();
}
