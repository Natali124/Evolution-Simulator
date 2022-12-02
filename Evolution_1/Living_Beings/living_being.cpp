#include "environment.h"
#include "living_being.h"

LivingBeing::LivingBeing() {
    alive = true;
    color = QColor(265, 0, 0, 127);
}

void LivingBeing::reproduction(){};

void LivingBeing::advance(int step){

    if (!step) { return; };

    //play_step(); //Ruben's group function
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
}






