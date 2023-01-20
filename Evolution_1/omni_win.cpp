#include "omni_win.h"
#include "Living_Beings/creature.h"
#include "ui_omni_win.h"
#include <QRandomGenerator>


float c_size = 0;
float energy = 0;
float health = 0;
float eyesight = 0;
float visibility = 0;
float strength = 0;

omni_win::omni_win(Environment *environment, QWidget *parent) :
    QDialog(parent),
    environment(environment),
    ui(new Ui::omni_win)
{
    ui->setupUi(this);

    connect(ui->strength_c, SIGNAL(valueChanged(int)),ui->strength_s,SLOT(setValue(int)) );
    connect(ui->strength_s,SIGNAL(valueChanged(int)),ui->strength_c,SLOT(setValue(int)) );

    connect(ui->energy_c, SIGNAL(valueChanged(int)),ui->energy_s,SLOT(setValue(int)) );
    connect(ui->energy_s,SIGNAL(valueChanged(int)),ui->energy_c,SLOT(setValue(int)) );

    connect(ui->eyesight_c, SIGNAL(valueChanged(int)),ui->eyesight_s,SLOT(setValue(int)) );
    connect(ui->eyesight_s,SIGNAL(valueChanged(int)),ui->eyesight_c,SLOT(setValue(int)) );

    connect(ui->visibility_c, SIGNAL(valueChanged(int)),ui->visibility_s,SLOT(setValue(int)) );
    connect(ui->visibility_s,SIGNAL(valueChanged(int)),ui->visibility_c,SLOT(setValue(int)) );

    connect(ui->health_c, SIGNAL(valueChanged(int)),ui->health_s,SLOT(setValue(int)) );
    connect(ui->health_s,SIGNAL(valueChanged(int)),ui->health_c,SLOT(setValue(int)) );

    connect(ui->size_c, SIGNAL(valueChanged(int)),ui->size_s,SLOT(setValue(int)) );
    connect(ui->size_s,SIGNAL(valueChanged(int)),ui->size_c,SLOT(setValue(int)) );

    ui->strength_c->setStyleSheet("color: black; background-color: white");
    ui->visibility_c->setStyleSheet("color: black; background-color: white");
    ui->size_c->setStyleSheet("color: black; background-color: white");
    ui->health_c->setStyleSheet("color: black; background-color: white");
    ui->eyesight_c->setStyleSheet("color: black; background-color: white");
    ui->energy_c->setStyleSheet("color: black; background-color: white");

    ui->strength_l->setStyleSheet("color: black");
    ui->visibility_l->setStyleSheet("color: black");
    ui->size_l->setStyleSheet("color: black");
    ui->health_l->setStyleSheet("color: black");
    ui->eyesight_l->setStyleSheet("color: black");
    ui->energy_l->setStyleSheet("color: black");

    ui->add_omnitrix->setStyleSheet("color: black; background-color: white");
    ui->randbut->setStyleSheet("color: black; background-color: white");
    ui->resetbut->setStyleSheet("color: black; background-color: white");
    ui->groupBox->setStyleSheet("color: black");




    QString back(":/backgrounds/images/gradient_1.jpg");
    setBackgroundImage(back);
}

void omni_win::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}

void omni_win::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    //fitDisplay();

    QDialog::resizeEvent(evt); //call base implementation
}

void omni_win::stretchBackground(){
    QString back(":/backgrounds/images/gradient_1.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}

omni_win::~omni_win()
{
    delete ui;
}

void omni_win::on_randbut_clicked()
{
    ui->size_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->health_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->strength_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->visibility_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->energy_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->eyesight_s->setValue(QRandomGenerator::global()->bounded(200));
}


void omni_win::on_resetbut_clicked()
{
    ui->size_s->setValue(0);
    ui->health_s->setValue(0);
    ui->strength_s->setValue(0);
    ui->visibility_s->setValue(0);
    ui->energy_s->setValue(0);
    ui->eyesight_s->setValue(0);
}


void omni_win::on_add_omnitrix_clicked()
{
    auto omni = new Creature;
    omni->setObjectName("Omnivore x");
    omni->parameters[Creature::eat_creature] = 1;
    omni->environment = environment;

    c_size += ui->size_c->value();
    energy += ui->energy_c->value();
    health += ui->health_c->value();
    eyesight += ui->eyesight_c->value();
    visibility += ui->visibility_c->value();
    strength += ui->strength_c->value();


    omni->set_size(c_size);
    omni->set_Max_energy(energy);
    omni->set_energy(energy);
    omni->set_Max_hp(health);
    omni->set_hp(health);
    omni->set_eye_sight(eyesight);
    omni->set_visibility(visibility);
    omni->set_physical_strength(strength);

    int maxX = environment->width();
    int maxY = environment->height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;
    omni->setPos(x, y);


    environment->addItem(omni);

    c_size = 0;
    energy = 0;
    health = 0;
    eyesight = 0;
    visibility = 0;
    strength = 0;

    this->close();
}

