#include "mainwindow.h"
#include "ui_mainwindow.h"

int num_pred = 0;
int num_prey = 0;
int num_plant = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->simBut->setVisible(false);

    ui->button_prey->setVisible(false);
    ui->button_pred->setVisible(false);
    ui->button_plant->setVisible(false);

    ui->count_pred->setVisible(false);
    ui->count_prey->setVisible(false);
    ui->count_plant->setVisible(false);

    ui->line_1->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);

    ui->creature_list->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_startBut_clicked()
{
    ui->startBut->setVisible(false);
    ui->simBut->setVisible(true);
    ui->button_prey->setVisible(true);
    ui->button_pred->setVisible(true);
    ui->button_plant->setVisible(true);
    ui->count_pred->setVisible(true);
    ui->count_prey->setVisible(true);
    ui->count_plant->setVisible(true);
    ui->line_1->setVisible(true);
    ui->line_2->setVisible(true);
    ui->line_3->setVisible(true);
    ui->creature_list->setVisible(true);
}



void MainWindow::on_button_pred_clicked()
{
    int val = ui->count_pred->value();
    qDebug() << "Predators:" << val;



    for (int i = num_pred; i < num_pred+val; i++) {
        ui->creature_list->addItem("Predator " + QString::number(i+1));
    }

    num_pred += val;

}


void MainWindow::on_button_prey_clicked()
{
    int val = ui->count_prey->value();
    qDebug() << "Prey:" << val;

    for (int i = num_prey; i < num_prey+val; i++) {
        ui->creature_list->addItem("Prey " + QString::number(i+1));
    }

    num_prey += val;
}


void MainWindow::on_button_plant_clicked()
{
    int val = ui->count_plant->value();
    qDebug() << "Plants:" << val;

    for (int i = num_plant; i < num_plant+val; i++) {
        ui->creature_list->addItem("Plant " + QString::number(i+1));
    }

    num_plant += val;

}


