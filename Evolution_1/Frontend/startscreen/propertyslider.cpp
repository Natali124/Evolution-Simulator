#include "propertyslider.h"
#include "ui_propertyslider.h"

PropertySlider::PropertySlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertySlider)
{
    ui->setupUi(this);
    show();
}

PropertySlider::~PropertySlider()
{
    delete ui;
}
