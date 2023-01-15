#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include "Neural_Network/reading.hpp"
#include "Neural_Network/nn_evolution.hpp"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationView menu(new Environment());
    MainWindow w; //start screen window
    w.show();

    return a.exec();
}*/

int main(){

    Network* nn = new Network(2, 2, 2, 2);
    Layer* inpt_layer = nn->get_input_layer();
    inpt_layer->value_vector();
    string path = "/Users/anjamatic/CSE201/";
    nn->network_to_vector();

    nn->network_to_file(path + "test_graph.txt");

    Network nn2 = file_to_network("test_graph.txt");

    return 0;
}
