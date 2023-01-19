#ifndef ENVIRONMENT_STATS_H
#define ENVIRONMENT_STATS_H


#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QStringList>
#include <QBarSeries>
#include <QBarSet>
#include <QAbstractAxis>
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
    std::vector<double> creature_energy_ratio(); //helper vector for creating a graph on the proportion of creatures having
    //certain percentages of hp (their hp/ their max_hp)
    ~Environment_Stats();
    void timerEvent(QTimerEvent *event);
    void update_chart();
    QChart* get_chart() {return chart;};
    SimulationView* get_menu() {return menu;};
    void set_menu(SimulationView* menu) {this->menu = menu; };
    void set_env(Environment* env) {this->env = env;};
    void set_x_axis(QAbstractAxis* x_axis) {this->x_axis =x_axis;};
    QAbstractAxis* get_x_axis() {return x_axis;};
    void set_y_axis(QAbstractAxis* y_axis) {this->y_axis =y_axis;};
    QAbstractAxis* get_y_axis() {return y_axis;};
    Environment* get_env() {return env;};
    std::map<Creature::Enum_parameters, double> average_creatures();
    std::map<Creature::Enum_parameters, double> average_prey();
    std::map<Creature::Enum_parameters, double> average_predator();
    void average_lifespan(int age);
    int number_LBs;
    int number_LBs_alive;
    int number_LBs_dead;
    int number_creatures;
    int number_creatures_alive;
    int number_creatures_dead;
    int number_plants;
    int number_plants_alive;
    int number_plants_dead;
    int last_50_ages[50];
    int number_ages = 0;


private:
    SimulationView* menu;
    QChart *chart {chart = new QChart()};
    Environment* env;
    QAbstractAxis* x_axis;
    QAbstractAxis* y_axis;

};

class Environment_Stats2 : QChartView {
public:
    Environment_Stats2(SimulationView* menu, QWidget* parent = nullptr);
    //std::vector<double> creature_energy_ratio(); //helper vector for creating a graph on the proportion of creatures having
    ~Environment_Stats2();
    //void timerEvent(QTimerEvent *event);
class Average_param : QChartView {
public:
    Average_param(SimulationView* menu, QWidget* parent = nullptr);
    ~Average_param();
    void timerEvent(QTimerEvent *event);
    void update_chart();
    QChart* get_chart() {return chart;};
    SimulationView* get_menu() {return menu;};
    void set_menu(SimulationView* menu) {this->menu = menu; };
    void set_env(Environment* env) {this->env = env;};
    void set_x_axis(QAbstractAxis* x_axis) {this->x_axis =x_axis;};
    QAbstractAxis* get_x_axis() {return x_axis;};
    void set_y_axis(QAbstractAxis* y_axis) {this->y_axis =y_axis;};
    QAbstractAxis* get_y_axis() {return y_axis;};
    Environment* get_env() {return env;};
    std::map<Creature::Enum_parameters, double> average_creatures();
    std::map<Creature::Enum_parameters, double> average_prey();
    std::map<Creature::Enum_parameters, double> average_predator();
    qreal x_val;
    qreal y_val;

private:
    SimulationView* menu;
    QChart *chart;
    Environment* env;
    QAbstractAxis* x_axis;
    QAbstractAxis* y_axis;

    void set_series(QLineSeries *series) {this->series = series;};
    QLineSeries* get_series() {return series;};
    int get_t() {return t;};
    void set_t(int t){this->t=t;};
    void increase_t() {t++;};
    double get_size_avg();


private:
    SimulationView* menu;
    QChart *chart {chart = new QChart()};
    Environment* env;
    QAbstractAxis* x_axis;
    QAbstractAxis* y_axis;
    QLineSeries* series ;
    int t;

};

#endif // ENVIRONMENT_STATS_H


