#include "Frontend/Widgets/statView.h"
#include "Living_Beings/creature.h"
#include "environment.h"
#include "living_being.h"
#include "qpainter.h"
#include <QGraphicsItem>
#include <cmath>
#include <QDebug>


void LivingBeing::reproduction(){};

void LivingBeing::playstep(){
    setRotation(rotation() + 7);
}

void LivingBeing::advance(int phase){

    if (!phase)
        return;

    // skip the playstep function for now as it crashes the program
    setRotation(rotation() + environment->get_simulation_step());
    return;
    //-----------------------------

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

//    painter->setBrush(color);
//    painter->drawEllipse(-10, -20, 20, 40);

    //debug for seeing sight direction -> eye direction towards -y
    painter->setPen(Qt::blue);
    painter->drawLine(0,0,0,-50);

    painter->setPen(Qt::red);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
}

//spawns a window showing being's stats
void LivingBeing::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    auto view = new StatView(this);
}



LivingBeing::LivingBeing(Environment* environment) : environment(environment){
    alive = true;
    type = none;
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

std::string LivingBeing::get_type_string(){
    switch(type) {
        case LivingBeing::Type_LB::none:
            return "living being";
        case LivingBeing::Type_LB::creature:{
            auto creature = dynamic_cast<Creature*>(this);
            if(creature->get_eat_creature())
                return "predator";
            else
                return "prey";
            break;
        }
        case LivingBeing::Type_LB::plant:
            return "plant";
    }

    return "";
}
