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

class Energy_perc : QChartView {
public:
    Energy_perc(SimulationView* menu, QWidget* parent = nullptr);
    std::vector<double> creature_energy_ratio(); //helper vector for creating a graph on the proportion of creatures having
    //certain percentages of energy (their energy/ their max_energy)
    ~Energy_perc();
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
    int number_LBs;
    int number_LBs_alive;
    int number_LBs_dead;
    int number_creatures;
    int number_creatures_alive;
    int number_creatures_dead;
    int number_plants;
    int number_plants_alive;
    int number_plants_dead;



    void set_series_prey_min(QLineSeries *series) {this->series_prey_min = series;};
    QLineSeries* get_series_prey_min() {return series_prey_min;};
    void set_series_prey_plus(QLineSeries *series) {this->series_prey_plus = series;};
    QLineSeries* get_series_prey_plus() {return series_prey_plus;};
    void set_series_predator_min(QLineSeries *series) {this->series_predator_min = series;};
    QLineSeries* get_series_predator_min() {return series_predator_min;};
    void set_series_predator_plus(QLineSeries *series) {this->series_predator_plus = series;};
    QLineSeries* get_series_predator_plus() {return series_predator_plus;};
    int get_t() {return t;};
    void set_t(int t){this->t=t;};
    void increase_t() {t++;};


private:
    SimulationView* menu;
    QChart *chart {chart = new QChart()};
    Environment* env;
    QAbstractAxis* x_axis;
    QAbstractAxis* y_axis;
    QLineSeries* series_prey_min ;
    QLineSeries* series_prey_plus;
    QLineSeries* series_predator_min;
    QLineSeries* series_predator_plus;
    int t;

};

class Environment_Stats2 : QChartView {
public:
    Environment_Stats2(SimulationView* menu, QWidget* parent = nullptr);
    //std::vector<double> creature_energy_ratio(); //helper vector for creating a graph on the proportion of creatures having
    ~Environment_Stats2();
    //void timerEvent(QTimerEvent *event);
    void update_chart();
    QChart* get_chart() {return chart;};
    std::map<Creature::Enum_parameters, double> average_prey();
    std::map<Creature::Enum_parameters, double> average_predator();
    qreal x_val;
    qreal y_val;
    int last_50_ages[50];
    int number_ages = 0;
    void average_lifespan(int age);


private:
    SimulationView* menu;
    QChart *chart;
    Environment* env;
    QAbstractAxis* x_axis;
    QAbstractAxis* y_axis;

};

class Average_size : QChartView {
public:
    Average_size(SimulationView* menu, QWidget* parent = nullptr);
    ~Average_size();
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
    void set_series_prey(QLineSeries *series) {this->series_prey = series;};
    QLineSeries* get_series_predator() {return series_predator;};
    void set_series_plant(QLineSeries *series) {this->series_plant = series;};
    QLineSeries* get_series_plant() {return series_plant;};
    void set_series_predator(QLineSeries *series) {this->series_predator = series;};
    QLineSeries* get_series_prey() {return series_prey;};
    int get_t() {return t;};
    void set_t(int t){this->t=t;};
    void increase_t() {t++;};
    std::vector<double> get_size_avg();


private:
    SimulationView* menu;
    QChart *chart {chart = new QChart()};
    Environment* env;
    QAbstractAxis* x_axis;
    QAbstractAxis* y_axis;
    QLineSeries* series_prey ;
    QLineSeries* series_predator ;
    QLineSeries* series_plant;
    int t;

};

#endif // ENVIRONMENT_STATS_H


