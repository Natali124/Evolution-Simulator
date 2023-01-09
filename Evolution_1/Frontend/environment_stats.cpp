#include "environment_stats.h"


Environment_Stats::Environment_Stats(Environment *env, QWidget *parent): QChartView(parent)
{
    this->env = env;

    show();
}
