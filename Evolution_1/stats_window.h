#ifndef STATS_WINDOW_H
#define STATS_WINDOW_H
#include <mainwindow.h>
#include <QMainWindow>
#include <QAbstractSeries>
#include <QtCharts>
#include <QLineSeries>
#include <QPointF>
#include <QPainter>
#include <QChartView>



class StatsWindow : public QMainWindow {
    public:
        StatsWindow(QWidget *parent = nullptr);
        ~StatsWindow();

};


#endif // STATS_WINDOW_H


/*goals for the holidays , Pablo and Garance:
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

 * -
 * - find out how to display the graph on stats window and not the main window
 *
 *
 * - find how to get the input (attributes of living beings that are present in the environment)
*/
