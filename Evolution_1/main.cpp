#include "environment.h"
#include "mainmenu.h"
#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
#include "Neural_Network/nn_evolution.hpp"
#include "Neural_Network/utils.hpp"
#include <string>
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>
#include <QTimer>
#include <QTime>
#include <math.h>
#include <fstream>

using namespace std;
double foo(double x){
  return x+0.4;
}

int main(){
    Network* nn = new Network(5, 2, 3, 2);
    vector<vector<double>> vect = nn->network_to_vector();
    string path = "/Users/anjamatic/CSE201/";
    vector_to_file(vect,path + "vector_to_file_test.txt");
    nn->network_to_file(path + "test_file.txt");
    vector<vector<double>> vect2 = file_to_vector(path + "vect_test2.txt");
    Network* nn2 = vector_to_network(vect);
    nn->print_weights();
    nn2->print_weights();
    return 0;
}

/*int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QWidget *statswindow = new QWidget;
    statswindow->setWindowTitle("Statistics of the simulation");
    //
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MainMenu menu;
    menu.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &menu.display._scene, SLOT(advance()));
    timer.start(1000 / 33);

    return a.exec();


}*/
