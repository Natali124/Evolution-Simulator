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
    explicit PropertySlider(QString label, Creature*, void (Creature::*)(double), double init_value, QWidget *parent = nullptr);
    explicit PropertySlider(QString lable, Plant*, void (Plant::*)(double), double init_value, QWidget *parent = nullptr);

    ~PropertySlider();

    void update();
    void randomise();
    void reset();

private:
    Ui::PropertySlider *ui;
    LivingBeing* being;
    void (Creature::*creatureSetterFunc)(double);
    void (Plant   ::   *plantSetterFunc)(double);
    void init(QString text, double init_value);
};

#endif // PROPERTYSLIDER_H
