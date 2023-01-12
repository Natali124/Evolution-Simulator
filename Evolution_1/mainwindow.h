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
    void advance(int phase);
    int step;
    void set_step(int val);
    int get_step();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H

