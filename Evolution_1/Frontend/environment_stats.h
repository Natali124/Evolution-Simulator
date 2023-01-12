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
#include <Frontend/Widgets/simulationView.h>
#include <Living_Beings/creature.h>
#include <Living_Beings/living_being.h>
#include <Living_Beings/plant.h>
#include <QTimer>
#include <QTimerEvent>

class Environment_Stats : QChartView {
public:
    Environment* env;
    Environment_Stats(SimulationView& menu, QWidget* parent = nullptr);
    std::vector<double> creature_hp_ratio(SimulationView& menu); //helper vector for creating a graph on the proportion of creatures having
    //certain percentages of hp (their hp/ their max_hp)
    ~Environment_Stats();
    void timerEvent(QTimerEvent *event);
    QChart *chart {chart = new QChart()};
    void update_chart();
    QChart* get_chart() {return chart;};
    void average_creatures(SimulationView& menu);


};



#endif // ENVIRONMENT_STATS_H


