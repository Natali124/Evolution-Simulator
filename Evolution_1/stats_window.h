#ifndef STATS_WINDOW_H
#define STATS_WINDOW_H
#include <QMainWindow>
#include <QAbstractSeries>
#include <QtCharts>
#include <QLineSeries>
#include <QPointF>
#include <QPainter>



/*class StatsWindow : public QMainWindow {
    public:
        StatsWindow(QWidget *parent = nullptr);
        ~StatsWindow();

};
*/
void example();



#endif // STATS_WINDOW_H


/*goals for this week, Pablo and Garance: (changes made in the cmake list, should compile now)
 *
 * - install qtcharts module with the QT Maintenance Tool
 *
 *
 * - find ideas of what stats to analyze
 *
 * x : time (one unit = ? playsteps )
 * y1 : nb of LB
 * y2 : life expectancy
 * different groups : plants VS creatures, groups separated by "barriers" when implemented

 * - learn how to display simple graphs
 * - maybe try to display a simple graph on a false input
 * - find how to get the input (attributes of living beings that are present in the environment)
*/
