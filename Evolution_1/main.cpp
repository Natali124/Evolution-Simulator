#include "Frontend/startscreen.h"
#include "Frontend/startscreen/propertyslider.h"
#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new startscreen;
    new PropertySlider;

    return a.exec();
}
