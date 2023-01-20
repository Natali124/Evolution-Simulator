#include "plant_win.h"
#include "Living_Beings/plant.h"
#include "ui_plant_win.h"
#include "Frontend/Widgets/simulationView.h"
#include "mainwindow.h"

float p_size = 0;
float max_hp = 0;
float reproduction = 0;

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

