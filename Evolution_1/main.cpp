#include "environment.h"
#include "mainmenu.h"
#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
#include "Neural_Network/nn_evolution.hpp"
#include <string>
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



int main(){
    Network nn = Network(5, 5);
    Layer* layer = nn.get_input_layer();
    vector<vector<double>> vect = nn.network_to_vector();
    vector_to_file(vect, "test.txt");
    nn.network_to_file("test.txt");


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
