#include "simulationViewWidgets.h"

EnvironmentTimer::EnvironmentTimer(Environment *environment) : environment(environment)
{
    // create a timer
    timer = new QTimer(this);
    timer->setInterval(baseStep);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(Slot()));
}

void EnvironmentTimer::Slot()
{
    environment->advance();
}
void EnvironmentTimer::start(){
    // milisec - 33fps
//    timer->start(1000 / 33);
    timer->start(timeStep);
}
void EnvironmentTimer::stop(){
    timer->stop();
}
void EnvironmentTimer::setStep(int percent){
    percent = std::max(percent, 1);
    percent = std::min(percent, 200);

    timeStep = baseStep * ( 200 - percent) / 100;
    //qDebug() << timeStep;
    timer->setInterval(timeStep);
}
