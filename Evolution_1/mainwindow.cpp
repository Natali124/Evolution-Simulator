#include "mainwindow.h"
#include "ui_mainwindow.h"

int num_pred = 0;
int num_prey = 0;
int num_plant = 0;
int active_creature;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->simBut->setVisible(false);

    ui->button_prey->setVisible(false);
    ui->button_pred->setVisible(false);
    ui->button_plant->setVisible(false);
    ui->button_delete_all->setVisible(false);

    ui->count_pred->setVisible(false);
    ui->count_prey->setVisible(false);
    ui->count_plant->setVisible(false);

    ui->line_1->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);

    ui->creature_list->setVisible(false);

    ui->groupBox->setVisible(false);

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
    ui->button_delete_all->setVisible(true);
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


void MainWindow::on_button_delete_all_clicked()
{
    ui->creature_list->clear();
    num_pred = 0;
    num_plant = 0;
    num_prey = 0;
}


void MainWindow::on_button_rdm_clicked()
{
    ui->eat_creature->setCheckState(Qt::Unchecked);
    ui->eat_plant->setCheckState(Qt::Unchecked);

    ui->P_strength_n->setValue(arc4random() % 101);
    ui->eye_sight_n->setValue(arc4random() % 101);
    ui->max_energy_n->setValue(arc4random() % 101);
    ui->size_n->setValue(arc4random() % 101);
    ui->max_health_n->setValue(arc4random() % 101);
    ui->visibility_n->setValue(arc4random() % 101);

    int val = arc4random() % 3;
    if (val == 0) {
        ui->eat_creature->setCheckState(Qt::Checked);
    }
    else if (val == 1) {
        ui->eat_creature->setCheckState(Qt::Checked);
        ui->eat_plant->setCheckState(Qt::Checked);
    }
    else if (val == 2) {
        ui->eat_plant->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_button_reset_clicked()
{
    ui->eat_creature->setCheckState(Qt::Unchecked);
    ui->eat_plant->setCheckState(Qt::Unchecked);
    ui->P_strength_n->setValue(0);
    ui->eye_sight_n->setValue(0);
    ui->max_energy_n->setValue(0);
    ui->size_n->setValue(0);
    ui->max_health_n->setValue(0);
    ui->visibility_n->setValue(0);
}

