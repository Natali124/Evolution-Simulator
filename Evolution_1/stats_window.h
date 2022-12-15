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


/*goals for this week, Pablo and Garance: (changes made in the cmake list, should compile now)
 *
 * - install qtcharts module with the QT Maintenance Tool
 *
 * - find how to get the input (attributes of living beings that are present in the environment)
 * - find ideas of what stats to analyze
 * - learn how to display simple graphs
 * - maybe try to display a simple graph on a false input
*/
