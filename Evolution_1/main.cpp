
#include "environment.h"
#include "mainmenu.h"
#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/reading.hpp"
#include "Neural_Network/nn_evolution.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>
#include <QTimer>
#include <QTime>
#include <math.h>


using namespace std;
double foo(double x){
  return x+0.4;
}
int main(int argc, char *argv[])
{

//    QApplication a(argc, argv);

//    QWidget *statswindow = new QWidget;
//    statswindow->setWindowTitle("Statistics of the simulation");
//    //
//    srand(QTime(0,0,0).secsTo(QTime::currentTime()));

//    MainMenu menu;
//    menu.show();

//    QTimer timer;
//    QObject::connect(&timer, SIGNAL(timeout()), &menu.display._scene, SLOT(advance()));
//    timer.start(1000 / 33);

//    return a.exec();
  Network* nn = new Network(5,3,1,2);
  vector<vector<double>> vect = nn->network_to_vector();
  vector_to_file(vect,"test.txt");
  string path = "C:/Users/titar/Desktop/Uni/";
  nn->network_to_file(path + "test.txt");
  Network* nn2 = vector_to_network(vect);
  nn->print_weights();
  nn2->print_weights();
  Network* nn3 = file_to_network(path + "test.txt");
  nn3->print_weights();
  return 0;
}
