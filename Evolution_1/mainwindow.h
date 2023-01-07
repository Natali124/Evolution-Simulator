#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <Frontend/Widgets/simulationView.h>
#include <Frontend/Widgets/simulationViewWidgets.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(SimulationView& menu, QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<double> creature_hp_ratio(SimulationView& menu); //helper vector for creating a graph on the proportion of creatures having
    //certain percentages of hp (their hp/ their max_hp)

private:
    Ui::MainWindow *ui;
};


class Chart : QChart {
public:
    Environment* env;
    void advance(int phase);
    int step;
    void set_step(int val);
    int get_step();
};


#endif // MAINWINDOW_H

