
#include "environment.h"
#include "mainmenu.h"
#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
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

    QApplication a(argc, argv);

    srand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MainMenu menu;
    menu.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &menu.display._scene, SLOT(advance()));
    timer.start(1000 / 33);

    return a.exec();

}
