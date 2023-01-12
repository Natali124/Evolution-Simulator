#include "environment_stats.h"


Environment_Stats::Environment_Stats(SimulationView& menu, QWidget *parent): QChartView(parent)
{
    this->env = menu.get_environment();


    //chart1:
    //QScatterSeries *LBs = new QScatterSeries();
    //QScatterSeries *Creatures = new QScatterSeries();
    //QScatterSeries *Plants = new QScatterSeries();

    //chart2:
    //QBarSet *alive = new QBarSet("alive");
    //QBarSet *dead = new QBarSet("dead");
    //QBarSet *tn = new QBarSet("total_number");

    //chart3:
    QBarSet *prop = new QBarSet("proportion of creatures having ...% of their max_hp  (random for now, working on it)");

    //chart2:
    //*alive << number_LBs_alive << number_creatures_alive << number_plants_alive;
    //*dead <<number_LBs_dead << number_creatures_dead << number_plants_dead;
    //*tn << number_LBs << number_creatures << number_plants;

    //charts 2,3:
    QBarSeries *series = new QBarSeries();

    //chart 3:
    //for now I put random values in proportion because no LBs in the environment
    //but when there will be, prop should have the five numbers n1 ,..,n5 multiplied by 10 to see them more clearly bcse they are ratios between 0 and 1
    //std::vector<double> v = creature_hp_ratio(menu);
    //for (std::vector<double>::iterator j=v.begin();j!=v.end(); j++) {
    //    prop->append((*j)*10);
    //}
    *prop << 3.1 << 1.0 << 3.2 << 1.7 << 1.0 ;
    series->append(prop);

    //chart2:
    //series->append(alive);
    //series->append(dead);
    //series->append(tn);

    //chart1:
    //LBs->append(0, number_LBs);
    //Creatures->append(1, number_creatures);
    //Plants->append(2, number_plants);

    //all charts:
    QChart *chart = new QChart();
    setChart(chart);
    //?
    //*chart->advance(int phase)

    //charts 2,3:
    chart->addSeries(series);

    //chart1:
    //chart->addSeries(LBs);
    //chart->addSeries(Creatures);
    //chart->addSeries(Plants);
    //chart->createDefaultAxes();

    //charts 1 , 2:
    //chart->setTitle("Number of LBs, Creatures and Plants (random for now)");

    //charts 2,3:
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;

    //chart2:
    //categories << "LBs" << "Creatures" << "Plants";

    //chart3:
    categories << "0 to 20%" << "21% to 40%" << "41% to 60%" << "61% to 80%" << "81% to 100%";

    //charts 2,3:
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //all charts:
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    show();
    this->update();
}
