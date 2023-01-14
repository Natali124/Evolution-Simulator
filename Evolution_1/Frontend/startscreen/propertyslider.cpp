#include "propertyslider.h"
#include "Living_Beings/living_being.h"
#include "ui_propertyslider.h"


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
    ui->label->setText(text);
    ui->spinBox->setValue((int)init_value);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &PropertySlider::update);
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
