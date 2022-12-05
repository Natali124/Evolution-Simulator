#include "environment.h"
#include "living_being.h"

#include <QGraphicsItem>
#include <cmath>


void LivingBeing::reproduction(){};

void LivingBeing::playstep(){};

void LivingBeing::advance(int step){

    if (!step) { return; };
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
}


LivingBeing::LivingBeing(){
    alive = true;
    type = none;
}




bool LivingBeing::get_alive() {return alive;};
void LivingBeing::set_alive(bool b) {this->alive = b;};




void LivingBeing::set_bounding_rect(qreal x, qreal y, qreal width, qreal height) { //top left corner at x,y
    this->bounding_rect = QRectF(x, y, width, height);
}

void LivingBeing::set_shape() {   // for now preys and predators are circles, plants are rectangles
    QPainterPath path;
    if (this->type == 0) { // if the LB is a predator
        this->set_bounding_rect(10, 10, 6, 6); // values just for testing purposes, to be changed
        path.addEllipse((this->bounding_rect));
    }

    if (this->type == 1) { // if the LB is a prey
        this->set_bounding_rect(10, 10, 3, 3); // values just for testing purposes, to be changed
        path.addEllipse((this->bounding_rect));
    }

    else if (this->type == 2) { // if the LB is a plant
        this->set_bounding_rect(10, 10, 2, 2); //values just for testing purposes, to be changed
        path.addRect(10, 10, 2, 2);
    }

    this->shape = path;
}





LivingBeing* LivingBeing::reproduction(){};

void LivingBeing::is_eaten(LivingBeing &c){};
void LivingBeing::take_dmg(float dmg){};
float LivingBeing::get_size(){};
void LivingBeing::set_size(float s){};
float LivingBeing::get_hp(){};
void LivingBeing::set_hp(float h){};

