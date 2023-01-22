#include "plant_win.h"
#include "Living_Beings/plant.h"
#include "ui_plant_win.h"
#include <QRandomGenerator>
#include "Frontend/Widgets/simulationView.h"
#include "mainwindow.h"
//these variables allow us to save the values of the sliders to a specific being
double p_size = 0;
double max_hp = 0;
double reproduction = 0;
/*This function is a constructor for a class "plant_win" that inherits from QDialog.
It sets up connections between UI elements, sets the stylesheet for various UI elements and sets the background image for the dialog.*/
Plant_win::Plant_win(Environment *environment, QWidget *parent) :
    QDialog(parent),
    environment(environment),
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
    ui->resetbut->setStyleSheet("color: black; background-color: white");
    ui->groupBox->setStyleSheet("color: black");

    QString back(":/backgrounds/images/gradient_1.jpg");
    setBackgroundImage(back);
}
//This function sets a background image of the window
void Plant_win::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}
//This function stretches the background to the size of the window
void Plant_win::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    //fitDisplay();

    QDialog::resizeEvent(evt); //call base implementation
}
//Scales the background to the window through resizes
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
/*This function is called when the "randomise" button in the window is clicked.
It sets random values between 0-200 to the various parameters of the plants.*/
void Plant_win::on_randbut_clicked()
{
    ui->size_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->health_s->setValue(QRandomGenerator::global()->bounded(200));
    ui->reproduction_s->setValue(QRandomGenerator::global()->bounded(200));
}

//This function is called when the "reset" button in the window is clicked; it resets the various parameters of the plants to 0.
void Plant_win::on_resetbut_clicked()
{
    ui->size_s->setValue(0);
    ui->health_s->setValue(0);
    ui->reproduction_s->setValue(0);
}
//Function creates a new plant and adds it to environment with selected parameters during ongoing simulation.
void Plant_win::on_add_plant1_clicked()
{
    auto plant = new Plant;
    plant->setObjectName("Plant x");
    plant->environment = environment;

    p_size += ui->size_c->value();
    max_hp += ui->health_c->value();
    reproduction += ui->reproduction_c->value();

    plant->set_size(p_size);
    plant->set_Max_hp(max_hp);
    plant->set_hp(max_hp);
    plant->set_reproduction_rate(reproduction);

    int maxX = environment->width();
    int maxY = environment->height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;
    plant->setPos(x, y);


    environment->addItem(plant);

    p_size = 0;
    max_hp = 0;
    reproduction = 0;

    this->close();

}

