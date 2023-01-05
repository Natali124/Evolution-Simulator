#include "environment.h"
#include "living_being.h"

#include <QGraphicsItem>
#include <cmath>


void LivingBeing::reproduction(){};

void LivingBeing::playstep(){
    setRotation(rotation() + 7);
}

void LivingBeing::advance(int step){

    if (!step)
        return;

    playstep(); //Ruben's group function
}

QRectF LivingBeing::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath LivingBeing::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}


void LivingBeing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);
    painter->drawRect(boundingRect());
}


LivingBeing::LivingBeing(){
    alive = true;
    type = none;
    setFlag(ItemIsMovable, true);
}
LivingBeing::~LivingBeing(){}



bool LivingBeing::get_alive() {return alive;};
void LivingBeing::set_alive(bool b) {this->alive = b;};


void LivingBeing::is_eaten(LivingBeing &c){};
void LivingBeing::take_dmg(float dmg){};
float LivingBeing::get_size(){};
void LivingBeing::set_size(float s){};
float LivingBeing::get_hp(){};
void LivingBeing::set_hp(float h){};

