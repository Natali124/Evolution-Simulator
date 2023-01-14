#include "startscreen.h"
#include "ui_startscreen.h"

#include <mainwindow.h>

startscreen::startscreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startscreen)
{
    ui->setupUi(this);
    show();
}

startscreen::~startscreen()
{
    delete ui;
}

void startscreen::on_StartBut_clicked()
{
    new MainWindow;
}

