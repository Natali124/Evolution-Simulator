#include "propertyslider.h"
#include "Living_Beings/living_being.h"
#include "ui_propertyslider.h"
#include <QRandomGenerator>

PropertySlider::PropertySlider(QString text, Creature* being, void (Creature::*setterFunc)(float), float init_value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertySlider),
    being(being),
    creatureSetterFunc(setterFunc)
{
    ui->setupUi(this);
    init(text, init_value);
    show();
}

PropertySlider::PropertySlider(QString text, Plant* being, void (Plant::*setterFunc)(float), float init_value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertySlider),
    being(being),
    plantSetterFunc(setterFunc)
{
    ui->setupUi(this);
    init(text, init_value);
    show();
}

PropertySlider::~PropertySlider()
{
    delete ui;
}

void PropertySlider::init(QString text, float init_value){
    setObjectName("Property Slider");
    ui->label->setText(text);
    ui->spinBox->setValue((int)init_value);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &PropertySlider::update);

//    QPalette pal = QPalette();
//    pal.setColor(QPalette::Window, Qt::transparent);

    //ui->horizontalSlider->setPalette(pal);
    //ui->horizontalSlider->setStyleSheet("color: grey; border: none");
    ui->horizontalSlider->setStyleSheet("QSlider::handle:horizontal {color: black; border: none; background-color: grey;}");
    ui->horizontalSlider->setStyleSheet("color: grey; border: none");
    //ui->spinBox->setPalette(pal)
    ui->spinBox->setStyleSheet("color: black; background-color: white");
    ui->label->setFrameShape(QFrame::Box);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setStyleSheet("border: none; background-color: grey");
}

void PropertySlider::update(){
    switch(being->type){
        case LivingBeing::Type_LB::creature:{
            auto creature = dynamic_cast<Creature*>(being);
            (creature->*creatureSetterFunc)(ui->spinBox->value());
            break;
        }
        case LivingBeing::Type_LB::plant:{
            auto plant = dynamic_cast<Plant*>(being);
            (plant->*plantSetterFunc)(ui->spinBox->value());
            break;
        }
        default:
            break;
    }

    qDebug()<<being->get_size();
}

void PropertySlider::randomise() {
   ui->horizontalSlider->setValue(QRandomGenerator::global()->bounded(200));
}

void PropertySlider::reset() {
   ui->horizontalSlider->setValue(0);
}
