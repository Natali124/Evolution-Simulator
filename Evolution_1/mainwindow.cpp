#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <Living_Beings/creature.h>
#include <Living_Beings/living_being.h>
#include <Living_Beings/plant.h>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //QScatterSeries *LBs = new QScatterSeries();
    //QScatterSeries *Creatures = new QScatterSeries();
    //QScatterSeries *Plants = new QScatterSeries();
    QBarSet *alive = new QBarSet("alive");
    QBarSet *dead = new QBarSet("dead");
    QBarSet *tn = new QBarSet("total_number");
    //*alive << number_LBs_alive << number_creatures_alive << number_plants_alive;
    *alive << number_LBs_alive << number_creatures_alive << (number_LBs_alive - number_creatures_alive);
    *dead <<number_LBs_dead << number_creatures_dead << number_plants_dead;
    //*tn << number_LBs << number_creatures << number_plants;
    *tn << number_LBs << number_creatures << (number_LBs - number_creatures);
    QBarSeries *series = new QBarSeries();
    series->append(alive);
    series->append(dead);
    series->append(tn);

    //LBs->append(0, number_LBs);
    //Creatures->append(1, number_creatures);
    //Plants->append(2, number_plants);
    QChart *chart = new QChart();
    chart->addSeries(series);
    //chart->addSeries(LBs);
    //chart->addSeries(Creatures);
    //chart->addSeries(Plants);
    //chart->createDefaultAxes();
    chart->setTitle("Number of LBs, Creatures and Plants");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "LBs" << "Creatures" << "Plants";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);



}

MainWindow::~MainWindow()
{
    delete ui;
}

