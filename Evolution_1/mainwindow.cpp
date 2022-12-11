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

    ui->Title->setVisible(false);

    ui->P_strength_n->setVisible(false);
    ui->P_strength_s->setVisible(false);
    ui->P_strength_t->setVisible(false);

    ui->eat_creature->setVisible(false);
    ui->eat_plant->setVisible(false);
    ui->eat_t->setVisible(false);

    ui->eye_sight_n->setVisible(false);
    ui->eye_sight_s->setVisible(false);
    ui->eye_sight_t->setVisible(false);

    ui->max_energy_n->setVisible(false);
    ui->max_energy_s->setVisible(false);
    ui->max_energy_t->setVisible(false);

    ui->size_n->setVisible(false);
    ui->size_s->setVisible(false);
    ui->size_t->setVisible(false);

    ui->max_health_n->setVisible(false);
    ui->max_health_s->setVisible(false);
    ui->max_health_t->setVisible(false);

    ui->visibility_n->setVisible(false);
    ui->visibility_s->setVisible(false);
    ui->visibility_t->setVisible(false);

    ui->button_rdm->setVisible(false);

//    // I set it visible for now so I can't test a few things
//    ui->Title->setVisible(true);

//    ui->P_strength_n->setVisible(true);
//    ui->P_strength_s->setVisible(true);
//    ui->P_strength_t->setVisible(true);

//    ui->eat_creature->setVisible(true);
//    ui->eat_plant->setVisible(true);
//    ui->eat_t->setVisible(true);

//    ui->eye_sight_n->setVisible(true);
//    ui->eye_sight_s->setVisible(true);
//    ui->eye_sight_t->setVisible(true);

//    ui->max_energy_n->setVisible(true);
//    ui->max_energy_s->setVisible(true);
//    ui->max_energy_t->setVisible(true);

//    ui->size_n->setVisible(true);
//    ui->size_s->setVisible(true);
//    ui->size_t->setVisible(true);

//    ui->max_health_n->setVisible(true);
//    ui->max_health_s->setVisible(true);
//    ui->max_health_t->setVisible(true);

//    ui->visibility_n->setVisible(true);
//    ui->visibility_s->setVisible(true);
//    ui->visibility_t->setVisible(true);

//    ui->button_rdm->setVisible(true);

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
