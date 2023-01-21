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

    ui->horizontalSlider->setStyleSheet("border:none ; height: 13px");
    ui->spinBox->setStyleSheet("color: black; background-color: white");
    ui->label->setFrameShape(QFrame::Box);
    ui->label->setMaximumHeight(21);
    ui->label->setStyleSheet("color: white; background-color: grey");
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
