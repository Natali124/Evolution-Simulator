#include "herb_win.h"
#include "Living_Beings/creature.h"
#include "ui_herb_win.h"
#include <QRandomGenerator>
//these variables allow us to save the values of the sliders to a specific being
double c_size = 0;
double energy = 0;
double health = 0;
double eyesight = 0;
double visibility = 0;
double strength = 0;
/*This function is a constructor for a class "herb_win" that inherits from QDialog.
It sets up connections between UI elements, sets the stylesheet for various UI elements and sets the background image for the dialog.*/
herb_win::herb_win(Environment *environment, QWidget *parent) :
    QDialog(parent),
    environment(environment),
    ui(new Ui::herb_win)
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

    ui->add_herbi->setStyleSheet("color: black; background-color: white");
    ui->randbut->setStyleSheet("color: black; background-color: white");
    ui->resetbut->setStyleSheet("color: black; background-color: white");
    ui->groupBox->setStyleSheet("color: black");

    QString back(":/backgrounds/images/gradient_1.jpg");
    setBackgroundImage(back);
}
//This function sets a background image of the window
void herb_win::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}
//This function stretches the background to the size of the window
void herb_win::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    //fitDisplay();

    QDialog::resizeEvent(evt); //call base implementation
}
//Scales the background to the window through resizes
void herb_win::stretchBackground(){
    QString back(":/backgrounds/images/gradient_1.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}

herb_win::~herb_win()
{
    delete ui;
}
/*This function is called when the "randomise" button in the window is clicked.
It sets random values between 0-200 to the various parameters of the creatures.*/
void herb_win::on_randbut_clicked()
{
    ui->size_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->health_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->strength_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->visibility_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->energy_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->eyesight_s->setValue(QRandomGenerator::global()->bounded(200));
}

//This function is called when the "reset" button in the window is clicked. It resets the various parameters of the creatures to 0.
void herb_win::on_resetbut_clicked()
{
    ui->size_s->setValue(0);
    ui->health_s->setValue(0);
    ui->strength_s->setValue(0);
    ui->visibility_s->setValue(0);
    ui->energy_s->setValue(0);
    ui->eyesight_s->setValue(0);
}

//Function creates a new herbivore creature and adds it to environment with selected parameters during ongoing simulation.
void herb_win::on_add_herbi_clicked()
{
    auto herbi = new Creature;
    herbi->setObjectName("Herbivore x");
    herbi->environment = environment;

    c_size += ui->size_c->value();
    energy += ui->energy_c->value();
    health += ui->health_c->value();
    eyesight += ui->eyesight_c->value();
    visibility += ui->visibility_c->value();
    strength += ui->strength_c->value();


    herbi->set_size(c_size);
    herbi->set_Max_energy(energy);
    herbi->set_energy(energy);
    herbi->set_Max_hp(health);
    herbi->set_hp(health);
    herbi->set_eye_sight(eyesight);
    herbi->set_visibility(visibility);
    herbi->set_physical_strength(strength);

    int maxX = environment->width();
    int maxY = environment->height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;
    herbi->setPos(x, y);


    environment->addItem(herbi);

    c_size = 0;
    energy = 0;
    health = 0;
    eyesight = 0;
    visibility = 0;
    strength = 0;

    this->close();

}

