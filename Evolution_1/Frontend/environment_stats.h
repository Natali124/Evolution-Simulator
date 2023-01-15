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
#include "Living_Beings/creature.h"

class Environment_Stats : QChartView {
public:
    Environment_Stats(SimulationView* menu, QWidget* parent = nullptr);
    std::vector<double> creature_hp_ratio(); //helper vector for creating a graph on the proportion of creatures having
    //certain percentages of hp (their hp/ their max_hp)
    ~Environment_Stats();
    void timerEvent(QTimerEvent *event);
    void update_chart();
    QChart* get_chart() {return chart;};
    SimulationView* get_menu() {return menu;};
    void set_menu(SimulationView* menu) {this->menu = menu; };
    void set_env(Environment* env) {this->env = env;};
    Environment* get_env() {return env;};
    int number_LBs;
    int number_LBs_alive;
    int number_LBs_dead;
    int number_creatures;
    int number_creatures_alive;
    int number_creatures_dead;
    int number_plants;
    int number_plants_alive;
    int number_plants_dead;
    std::map<Creature::Enum_parameters, double> average_creatures();

private:
    SimulationView* menu;
    QChart *chart {chart = new QChart()};
    Environment* env;


};



#endif // ENVIRONMENT_STATS_H


