#ifndef STATS_WINDOW_H
#define STATS_WINDOW_H
#include <QMainWindow>
#include <QAbstractSeries>
#include <QtCharts>




class StatsWindow : public QMainWindow {
    public:
        StatsWindow(QWidget *parent = nullptr);
        ~StatsWindow();

};



#endif // STATS_WINDOW_H
