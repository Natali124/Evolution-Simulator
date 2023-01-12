#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <Living_Beings/creature.h>
#include <Living_Beings/living_being.h>
#include <Living_Beings/plant.h>
#include "environment.h"
#include <Frontend/Widgets/simulationView.h>
#include <Frontend/Widgets/simulationViewWidgets.h>
#include <QGraphicsItem>

void MainWindow::advance(int phase) { //this function is used to update
    if (phase == 1) {
        this->set_step(this->get_step()+1);
    }
}
int MainWindow::get_step() {return this->step;}
void MainWindow::set_step(int val) {this->step = val;}

MainWindow::MainWindow(SimulationView& menu, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

