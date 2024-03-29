#include "Frontend/Widgets/statView.h"
#include "Living_Beings/creature.h"
#include "environment.h"
#include "living_being.h"
#include "qpainter.h"

#include <QGraphicsItem>
#include <cmath>



int LivingBeing::get_alive_time(){return this->alive_time;}
void LivingBeing::increase_alive_time(){if (alive_time<10000){alive_time++;}}

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

//QPainterPath LivingBeing::shape() const
//{
//    QPainterPath path;
//    //I divided by 200 since random the random constructor gives a size between 0 and 200, this might be temprorary values;
//    path.addRect(-5*get_size()/400, -10*get_size()/400, 10*get_size()/400, 20*get_size()/400);
//    return path;
//}


void LivingBeing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    /*painter->setBrush(color);
    //I divided by 200 since random the random constructor gives a size between 0 and 200, this might be temprorary values;
    painter->drawEllipse(-5*get_size()/400, -10*get_size()/400, 10*get_size()/400, 20*get_size()/400);*/
//    painter->drawRect(boundingRect());
//    painter->drawPath(shape());
}


LivingBeing::LivingBeing(){
    alive = true;
    type = none;
}


LivingBeing::~LivingBeing() {};

bool LivingBeing::get_alive()  {return alive;};
void LivingBeing::set_alive(bool b) {this->alive = b;};

LivingBeing* LivingBeing::reproduction(){return nullptr;};

void LivingBeing::is_eaten(LivingBeing &c){};
void LivingBeing::take_dmg(double dmg){};
double LivingBeing::get_size() const{return 20;};
void LivingBeing::set_size(double s){};
double LivingBeing::get_hp() {return -1;};
void LivingBeing::set_hp(double h){};
void LivingBeing::set_scene(Environment *s){environment = s;};
Environment* LivingBeing::get_scene() {return environment;};

void LivingBeing::set_family(int fam){};
int LivingBeing::get_family(){return -1;};

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

void LivingBeing::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    new StatView(this);
}
