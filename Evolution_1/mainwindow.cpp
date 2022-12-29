#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QScatterSeries *LBs = new QScatterSeries();
    QScatterSeries *Creatures = new QScatterSeries();
    QScatterSeries *Plants = new QScatterSeries();

    LBs->append(0, number_LBs);
    Creatures->append(1, number_creatures);
    Plants->append(2, number_plants);

    //series->append(0, 0);
    //series->append(1, 7);
    //series->append(2, 7);
    //series->append(3, 7);
    //series->append(4, 7);
    //*series << QPointF(0.5, 8) << QPointF(1.5, 8) << QPointF(2.5, 8) << QPointF(3.5, 8) << QPointF(4.5, 8);
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(LBs);
    chart->addSeries(Creatures);
    chart->addSeries(Plants);
    chart->createDefaultAxes();
    chart->setTitle("Number of LBs, Creatures and Plants");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);


}

MainWindow::~MainWindow()
{
    delete ui;
}

