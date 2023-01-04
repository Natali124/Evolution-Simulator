#include "environment.h"
#include "living_being.h"

#include <QGraphicsItem>
#include <cmath>


int number_LBs = 0;
int number_LBs_alive = 0;
int number_LBs_dead = 0;

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
    return QRectF((-18 - adjust)*get_size()/200, (-22 - adjust)*get_size()/200,
                  (36 + adjust)*get_size()/200, (60 + adjust)*get_size()/200);
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

//    painter->setBrush(color);
//    painter->drawEllipse(-10, -20, 20, 40);

    //debug for seeing sight direction -> eye direction towards -y
    painter->setPen(Qt::blue);
    painter->drawLine(0,0,0,-50);

    painter->setPen(Qt::red);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}


LivingBeing::LivingBeing(Environment* environment) : environment(environment){
    alive = true;
    type = none;
    number_LBs ++;
    number_LBs_alive ++;
}


LivingBeing::~LivingBeing() {};

bool LivingBeing::get_alive() const {return alive;};
void LivingBeing::set_alive(bool b) {this->alive = b;};








LivingBeing* LivingBeing::reproduction(){return nullptr;};

void LivingBeing::is_eaten(LivingBeing &c){};
void LivingBeing::take_dmg(double dmg){};
double LivingBeing::get_size() const{return -1;};
void LivingBeing::set_size(double s){};
double LivingBeing::get_hp() const{return -1;};
void LivingBeing::set_hp(double h){};
void LivingBeing::set_scene(QGraphicsScene *s){scene=s;};
QGraphicsScene* LivingBeing::get_scene() const {return scene;};

