#ifndef ENVIRONMENT_STATS_H
#define ENVIRONMENT_STATS_H



#include "environment.h"
#include "qchart.h"
#include "qchartview.h"

class Environment_Stats : QChartView {
public:
    Environment* env;
    Environment_Stats(Environment*, QWidget* parent = nullptr);

};



#endif // ENVIRONMENT_STATS_H


