#include "environment.h"
#include "living_being.h"

#include <QGraphicsItem>
#include <cmath>



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
    //I divided by 200 since random the random constructor gives a size between 0 and 200, this might be temprorary values;
    path.addRect(-10*get_size()/200, -20*get_size()/200, 20*get_size()/200, 40*get_size()/200);
    return path;
}


void LivingBeing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    painter->setBrush(color);
    //I divided by 200 since random the random constructor gives a size between 0 and 200, this might be temprorary values;
    painter->drawEllipse(-10*get_size()/200, -20*get_size()/200, 20*get_size()/200, 40*get_size()/200);
}


LivingBeing::LivingBeing(){
    alive = true;
    type = none;
}


LivingBeing::~LivingBeing() {};

bool LivingBeing::get_alive() const {return alive;};
void LivingBeing::set_alive(bool b) {this->alive = b;};








LivingBeing* LivingBeing::reproduction(){};

void LivingBeing::is_eaten(LivingBeing &c){};
void LivingBeing::take_dmg(double dmg){};
double LivingBeing::get_size() const{};
void LivingBeing::set_size(double s){};
double LivingBeing::get_hp() const{};
void LivingBeing::set_hp(double h){};

