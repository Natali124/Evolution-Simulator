#ifndef ENVIRONMENT_STATS_H
#define ENVIRONMENT_STATS_H


#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QStringList>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include "environment.h"
#include "qchart.h"
#include "qchartview.h"

class Environment_Stats : QChartView {
public:
    Environment* env;
    Environment_Stats(Environment*, QWidget* parent = nullptr);

};



#endif // ENVIRONMENT_STATS_H


