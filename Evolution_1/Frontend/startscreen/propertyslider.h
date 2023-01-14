#ifndef PROPERTYSLIDER_H
#define PROPERTYSLIDER_H

#include "Living_Beings/living_being.h"
#include "Living_Beings/plant.h"
#include <QWidget>

namespace Ui {
class PropertySlider;
}

class PropertySlider : public QWidget
{
    Q_OBJECT

public:
    explicit PropertySlider(QString label, Creature*, void (Creature::*)(float), float init_value, QWidget *parent = nullptr);
    explicit PropertySlider(QString lable, Plant*, void (Plant::*)(float), float init_value, QWidget *parent = nullptr);

    ~PropertySlider();

private:
    Ui::PropertySlider *ui;
    LivingBeing* being;
    void (Creature::*creatureSetterFunc)(float);
    void (Plant   ::   *plantSetterFunc)(float);
    void init(QString text, float init_value);
    void update();
};

#endif // PROPERTYSLIDER_H
