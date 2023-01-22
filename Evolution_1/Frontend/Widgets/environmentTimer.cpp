#include "simulationViewWidgets.h"
#include <iostream>

EnvironmentTimer::EnvironmentTimer(Environment *environment) : environment(environment)
{
    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(Slot()));
}

void EnvironmentTimer::Slot()
{
    environment->advance();
}
void EnvironmentTimer::start(){
    // milisec - 33fps
    timer->start(1000 / 33);
}
void EnvironmentTimer::stop(){
    timer->stop();
}
