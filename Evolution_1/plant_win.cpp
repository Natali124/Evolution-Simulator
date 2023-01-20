#include "plant_win.h"
#include "ui_plant_win.h"
#include <QRandomGenerator>

Plant_win::Plant_win(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Plant_win)
{
    ui->setupUi(this);
    connect(ui->health_c, SIGNAL(valueChanged(int)),ui->health_s,SLOT(setValue(int)) );
    connect(ui->health_s,SIGNAL(valueChanged(int)),ui->health_c,SLOT(setValue(int)) );

    connect(ui->reproduction_c, SIGNAL(valueChanged(int)),ui->reproduction_s,SLOT(setValue(int)) );
    connect(ui->reproduction_s,SIGNAL(valueChanged(int)),ui->reproduction_c,SLOT(setValue(int)) );

    connect(ui->size_c, SIGNAL(valueChanged(int)),ui->size_s,SLOT(setValue(int)) );
    connect(ui->size_s,SIGNAL(valueChanged(int)),ui->size_c,SLOT(setValue(int)) );

    ui->size_c->setStyleSheet("color: black; background-color: white");
    ui->health_c->setStyleSheet("color: black; background-color: white");
    ui->reproduction_c->setStyleSheet("color: black; background-color: white");


    ui->size_l->setStyleSheet("color: black");
    ui->health_l->setStyleSheet("color: black");
    ui->reproduction_l->setStyleSheet("color: black");


    ui->add_plant1->setStyleSheet("color: black; background-color: white");
    ui->randbut->setStyleSheet("color: black; background-color: white");
    ui->groupBox->setStyleSheet("color: black");

    QString back(":/backgrounds/images/gradient_1.jpg");
    setBackgroundImage(back);
}
void Plant_win::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}
void Plant_win::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    //fitDisplay();

    QDialog::resizeEvent(evt); //call base implementation
}

void Plant_win::stretchBackground(){
    QString back(":/backgrounds/images/gradient_1.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}


Plant_win::~Plant_win()
{
    delete ui;
}

void Plant_win::on_randbut_clicked()
{
    ui->size_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->health_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->reproduction_s->setValue(QRandomGenerator::global()->bounded(200));
}


void Plant_win::on_resetbut_clicked()
{
    ui->size_s->setValue(0);
    ui->health_s->setValue(0);
    ui->reproduction_s->setValue(0);
}

